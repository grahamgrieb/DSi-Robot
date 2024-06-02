/******************************************************************
 This is an example for the Adafruit RA8875 Driver board for TFT displays
 ---------------> http://www.adafruit.com/products/1590
 The RA8875 is a TFT driver for up to 800x480 dotclock'd displays
 It is tested to work with displays in the Adafruit shop. Other displays
 may need timing adjustments and are not guanteed to work.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#include <Wire.h>

#include <SPIFFS.h> // Add this line to include the SPIFFS library
#include <ESP32DMASPISlave.h>
#include <WiFi.h>
#include <ESPNowCam.h>
#include <JPEGENC.h>

JPEGENC jpg;
JPEGENCODE jpe;
ESP32DMASPI::Slave slave;

static uint8_t receiver[] = { 0xEC, 0xDA, 0x3B, 0x98, 0x68, 0x98 };
ESPNowCam radio;
#define send_size 30000
static constexpr size_t BUFFER_SIZE = 33000;
static constexpr size_t QUEUE_SIZE = 4;
uint8_t *bmp_buf1;
uint8_t *bmp_buf2;
uint8_t *bmp_buf3;
uint8_t *bmp_buf4;
//uint8_t* fb = (uint8_t*)  malloc(send_size) ;


void loop()
{
  // wait for the completion of the queued transactions

  Serial.println("Waiting for data");
  slave.queue(NULL, bmp_buf1, BUFFER_SIZE);
  slave.queue(NULL, bmp_buf2, BUFFER_SIZE);
  slave.queue(NULL, bmp_buf3, BUFFER_SIZE);
  slave.queue(NULL, bmp_buf4, 4);

  const std::vector<size_t> received_bytes = slave.wait();
  Serial.println("Data received");
  Serial.println(received_bytes[0]);
  Serial.println(received_bytes[1]);
  Serial.println(received_bytes[2]);
  Serial.println(received_bytes[3]);
  uint8_t* bitmap = (uint8_t*) ps_calloc(98304, sizeof(uint8_t));
  //copy four buffers to bitmap buffers

  memcpy(bitmap, bmp_buf1, received_bytes[0]);
  uint8_t first_byte = bmp_buf1[0];
  memcpy(bitmap + received_bytes[0], bmp_buf2, received_bytes[1]);
  memcpy(bitmap + received_bytes[0] + received_bytes[1], bmp_buf3, received_bytes[2]);
  memcpy(bitmap + received_bytes[0] + received_bytes[1] + received_bytes[2], bmp_buf4, 3);

 
  
  //create 25k buffer
  uint8_t *buffer = (uint8_t *)ps_calloc(25000, sizeof(uint8_t));


  jpg.open(buffer,25000);
  const int iWidth = 256, iHeight = 192;
  const int iBpp = 2; //24 bit color
  const int iPitch = iWidth * iBpp; //bytes per row
  
  int rc = jpg.encodeBegin(&jpe,iWidth,iHeight,JPEGE_PIXEL_RGB565,JPEGE_SUBSAMPLE_420,JPEGE_Q_BEST);
  int iDataSize;
 
  rc=jpg.addFrame(&jpe,bitmap,iPitch);
  
  iDataSize = jpg.close();
  Serial.print("Output file size = ");
  Serial.println(iDataSize, DEC);
  
  

  unsigned long startTime = millis();

  Serial.println(radio.sendData(buffer,iDataSize));
  
  Serial.printf("Elapsed Time: %lu ms\n", millis() - startTime);

  //free buffers
  free(bitmap);
  free(buffer);
  //send hello world
  //radio.sendData((uint8_t*)"Hello, world!", 13);
  delay (1000);
  

 
   

}




void setup () {  
  Serial.begin(9600);
  if( !psramInit() ) {
    Serial.println("PSRAM FAIL");
    while(1) {
      ;
    }
  }
  radio.init();
  radio.setTarget(receiver);
  


  // to use DMA buffer, use these methods to allocate buffer
  //dma_tx_buf = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf1 = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf2 = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf3 = slave.allocDMABuffer(BUFFER_SIZE);
  bmp_buf4 = slave.allocDMABuffer(4);

  slave.setDataMode(SPI_MODE3);           // default: SPI_MODE0
  slave.setMaxTransferSize(BUFFER_SIZE);  // default: 4092 bytes
  slave.setQueueSize(QUEUE_SIZE);         // default: 1, requres 2 in this example
  
  
  // begin() after setting
  slave.begin(HSPI);  // default: HSPI (please refer README for pin assignments)

}