#include <Wire.h>
#include <SPIFFS.h> // Add this line to include the SPIFFS library
#include <ESP32DMASPISlave.h>
#include <WiFi.h>
#include <ESPNowCam.h>
#include <JPEGENC.h>
#include <ArduinoWebsockets.h>
using namespace websockets;
TaskHandle_t Task1;
TaskHandle_t Task2;
JPEGENC jpg;
JPEGENCODE jpe;
ESP32DMASPI::Slave slave;

#define send_size 30000
static constexpr size_t BUFFER_SIZE = 33000;
static constexpr size_t QUEUE_SIZE = 4;
uint8_t *bmp_buf1;
uint8_t *bmp_buf2;
uint8_t *bmp_buf3;
uint8_t *bmp_buf4;
uint8_t movement = 4;
// Set your access point network credentials
const char *ssid = "Graham-ESP32";
const char *password = "123456789";

WebsocketsServer server;
WebsocketsClient client;
// uint8_t* fb = (uint8_t*)  malloc(send_size) ;

void loop()
{
  //Serial.println("Waiting for start signal");
  // wait for the completion of the queued transactions
  digitalWrite(13, HIGH);
  slave.queue(NULL, bmp_buf4, 4);
  const std::vector<size_t> received_bytes1 = slave.wait();
  if (received_bytes1[0] != 2 && (bmp_buf4[0] != 0x44 || bmp_buf4[0] != 0x33))
  {
    return;
  }

  if (bmp_buf4[1] != movement)
  {
    movement = bmp_buf4[1];
    Serial.println("Movement changed");
    while (!client.available())
    {
      client = server.accept();
    }
    client.send((char *)&bmp_buf4[1], 1);
  }
  //first byte is 0x33 which means it was just sending a direction, therefore return
  if (bmp_buf4[0] != 0x44)
  {
    return;
  }
  unsigned long startTime = millis();
  slave.queue(NULL, bmp_buf4, 4);
  const std::vector<size_t> received_bytes2 = slave.wait();
  if (received_bytes2[0] != 1)
  {
    return;
  }
  if (bmp_buf4[0] != 0x12)
  {
    return;
  }
  digitalWrite(13, LOW);
  Serial.println("Waiting for data");
  slave.queue(NULL, bmp_buf1, BUFFER_SIZE);
  slave.queue(NULL, bmp_buf2, BUFFER_SIZE);
  slave.queue(NULL, bmp_buf3, BUFFER_SIZE);
  slave.queue(NULL, bmp_buf4, 4);

  const std::vector<size_t> received_bytes = slave.wait();

  if (received_bytes[0] != 32767 || received_bytes[1] != 32767 || received_bytes[2] != 32767 || received_bytes[3] != 3)
  {
    Serial.printf("Not BMP: %d %d %d %d\n", received_bytes[0], received_bytes[1], received_bytes[2], received_bytes[3]);
    return;
  }

  Serial.println("Received BMP");
  Serial.printf("SPI Time: %lu ms\n", millis() - startTime);
  startTime = millis();
  uint8_t *bitmap = (uint8_t *)ps_calloc(98304, sizeof(uint8_t));
  // copy four buffers to bitmap buffers

  memcpy(bitmap, bmp_buf1, received_bytes[0]);
  memcpy(bitmap + received_bytes[0], bmp_buf2, received_bytes[1]);
  memcpy(bitmap + received_bytes[0] + received_bytes[1], bmp_buf3, received_bytes[2]);
  memcpy(bitmap + received_bytes[0] + received_bytes[1] + received_bytes[2], bmp_buf4, 3);

  // create 25k buffer
  uint8_t *jpg_buffer = (uint8_t *)ps_calloc(25000, sizeof(uint8_t));

  jpg.open(jpg_buffer, 25000);
  const int iWidth = 256, iHeight = 192;
  const int iBpp = 2;               // 24 bit color
  const int iPitch = iWidth * iBpp; // bytes per row

  int rc = jpg.encodeBegin(&jpe, iWidth, iHeight, JPEGE_PIXEL_RGB565, JPEGE_SUBSAMPLE_444, JPEGE_Q_BEST);
  int iDataSize;

  rc = jpg.addFrame(&jpe, bitmap, iPitch);
  if (rc != 0)
  {
    Serial.println("Error encoding");
  }

  iDataSize = jpg.close();
  free(bitmap);
  Serial.print("Output file size = ");
  Serial.println(iDataSize, DEC);
  Serial.printf("Encoding Time: %lu ms\n", millis() - startTime);

  startTime = millis();

  // radio.sendData(jpg_buffer, iDataSize);
  while (!client.available())
  {
    client = server.accept();
  }
  client.send((char *)jpg_buffer, iDataSize);

  free(jpg_buffer);
  Serial.printf("Send Time: %lu ms\n", millis() - startTime);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("ESP32-S3 DSi");
  pinMode(46, OUTPUT);
  digitalWrite(46, HIGH);
  if (!psramInit())
  {
    Serial.println("PSRAM FAIL");
    while (1)
    {
      ;
    }
  }
  // wifi code
  WiFi.begin(ssid, password);
  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to wifi");
  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("No Wifi!");
    return;
  }
  Serial.println("Connected to WiFi");
  server.listen(81);
  Serial.print("Is server live? ");
  Serial.println(server.available());

  client = server.accept();
  Serial.println("Done connecting");

  // webSocket.enableHeartbeat(1000,6000,3);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // to use DMA buffer, use these methods to allocate buffer
  // dma_tx_buf = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf1 = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf2 = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf3 = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf4 = slave.allocDMABuffer(4);

  slave.setDataMode(SPI_MODE3);          // default: SPI_MODE0
  slave.setMaxTransferSize(BUFFER_SIZE); // default: 4092 bytes
  slave.setQueueSize(QUEUE_SIZE);        // default: 1, requres 2 in this example

  slave.begin(HSPI); // default: HSPI (please refer README for pin assignments)
  Serial.println("SPI Slave initiatalized");

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.println("Setup complete");
}