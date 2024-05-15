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
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPNowCam.h>
static uint8_t receiver[] = { 0x8C, 0xCE, 0x4E, 0x8C, 0xB6, 0x88 };
ESPNowCam radio;
#define send_size 110000
uint8_t* fb = (uint8_t*)  malloc(send_size) ;







SPIClass * hspi = NULL;
static const int spiClk = 1000000;
ESP32DMASPI::Slave slave;
static constexpr size_t BUFFER_SIZE = 147600;
static constexpr size_t QUEUE_SIZE = 2;
uint8_t *dma_tx_buf;
uint8_t *dma_rx_buf;
int i=0;

void loop()
{
  /*slave.queue(NULL, dma_rx_buf, BUFFER_SIZE);

  // wait for the completion of the queued transactions
  const std::vector<size_t> received_bytes = slave.wait();
  Serial.println(received_bytes[0]);
  //save received data to SPIFFS
  File file = SPIFFS.open("/test.bmp", FILE_WRITE);
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
  file.write(dma_rx_buf, received_bytes[0]);
  file.close();*/
 // String message = "Hello, world!";
  //quickEspNow.send (DEST_ADDR, (uint8_t*)message.c_str (), message.length ());
  //send 200KB of data
  //send test.bmp over espnow
  File file = SPIFFS.open("/ds.bmp", FILE_READ);
  if (!file) {
    Serial.println("There was an error opening the file for reading");
    return;
  }
  //print file size
  Serial.println(file.size());
  
  //file.read(fb, file.size());
  
  radio.sendData(fb,send_size);
  //send hello world
  //radio.sendData((uint8_t*)"Hello, world!", 13);
  delay (1000);

  
   

}




void setup () {  
  Serial.begin(9600);
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  delay(2000);

  radio.init();
  radio.setTarget(receiver);

  // to use DMA buffer, use these methods to allocate buffer
  dma_tx_buf = slave.allocDMABuffer(BUFFER_SIZE);
  dma_rx_buf = slave.allocDMABuffer(BUFFER_SIZE);

  slave.setDataMode(SPI_MODE3);           // default: SPI_MODE0
  slave.setMaxTransferSize(BUFFER_SIZE);  // default: 4092 bytes
  slave.setQueueSize(QUEUE_SIZE);         // default: 1, requres 2 in this example
  
  // begin() after setting
  slave.begin();  // default: HSPI (please refer README for pin assignments)
  
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
  }

}