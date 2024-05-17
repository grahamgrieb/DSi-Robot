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
#include <WiFi.h>
#include <ESPNowCam.h>


ESPNowCam radio;
uint8_t *fb; 




void onDataReady(uint32_t len) {
  Serial.printf("Received %d bytes\n", len);
  //print first two bytes
  Serial.printf("First two bytes: %02X %02X\n", fb[0], fb[1]);
  
}



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
 

  
   

}




void setup () {  
  Serial.begin(9600);
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  delay(2000);

  fb = (uint8_t*)  malloc(98358* sizeof( uint8_t ) ) ;

  radio.setRecvBuffer(fb);
  radio.setRecvCallback(onDataReady);

  radio.init();
  
  


}