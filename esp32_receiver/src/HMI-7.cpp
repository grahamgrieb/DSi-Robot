#include <Arduino.h>
#include <lvgl.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <SPIFFS.h>
#include <ESPNowCam.h>
#include <SPI.h>
#include <Ticker.h>          //Call the ticker. H Library

ESPNowCam radio;
uint8_t * receive_buffer; 


SPIClass& spi = SPI;
uint16_t touchCalibration_x0 = 300, touchCalibration_x1 = 3600, touchCalibration_y0 = 300, touchCalibration_y1 = 3600;
uint8_t  touchCalibration_rotate = 1, touchCalibration_invert_x = 2, touchCalibration_invert_y = 0;
static int val = 100;

Ticker ticker1;

int i = 0;
//#include <Arduino_GFX_Library.h>
#define TFT_BL 2
// Define a class named LGFX, inheriting from the LGFX_Device class.
class LGFX : public lgfx::LGFX_Device {
public:
  // Instances for the RGB bus and panel.
  lgfx::Bus_RGB     _bus_instance;
  lgfx::Panel_RGB   _panel_instance;

  // Constructor for the LGFX class.
  LGFX(void) {
    // Configure the RGB bus.
    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;

      // Configure data pins.
      cfg.pin_d0  = GPIO_NUM_15; // B0
      cfg.pin_d1  = GPIO_NUM_7;  // B1
      cfg.pin_d2  = GPIO_NUM_6;  // B2
      cfg.pin_d3  = GPIO_NUM_5;  // B3
      cfg.pin_d4  = GPIO_NUM_4;  // B4
      
      cfg.pin_d5  = GPIO_NUM_9;  // G0
      cfg.pin_d6  = GPIO_NUM_46; // G1
      cfg.pin_d7  = GPIO_NUM_3;  // G2
      cfg.pin_d8  = GPIO_NUM_8;  // G3
      cfg.pin_d9  = GPIO_NUM_16; // G4
      cfg.pin_d10 = GPIO_NUM_1;  // G5
      
      cfg.pin_d11 = GPIO_NUM_14; // R0
      cfg.pin_d12 = GPIO_NUM_21; // R1
      cfg.pin_d13 = GPIO_NUM_47; // R2
      cfg.pin_d14 = GPIO_NUM_48; // R3
      cfg.pin_d15 = GPIO_NUM_45; // R4

      // Configure sync and clock pins.
      cfg.pin_henable = GPIO_NUM_41;
      cfg.pin_vsync   = GPIO_NUM_40;
      cfg.pin_hsync   = GPIO_NUM_39;
      cfg.pin_pclk    = GPIO_NUM_0;
      cfg.freq_write  = 15000000;

      // Configure timing parameters for horizontal and vertical sync.
      cfg.hsync_polarity    = 0;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 48;
      cfg.hsync_back_porch  = 40;
      
      cfg.vsync_polarity    = 0;
      cfg.vsync_front_porch = 1;
      cfg.vsync_pulse_width = 31;
      cfg.vsync_back_porch  = 13;

      // Configure polarity for clock and data transmission.
      cfg.pclk_active_neg   = 1;
      cfg.de_idle_high      = 0;
      cfg.pclk_idle_high    = 0;

      // Apply configuration to the RGB bus instance.
      _bus_instance.config(cfg);
    }

    // Configure the panel.
    {
      auto cfg = _panel_instance.config();
      cfg.memory_width  = 800;
      cfg.memory_height = 480;
      cfg.panel_width   = 800;
      cfg.panel_height  = 480;
      cfg.offset_x      = 0;
      cfg.offset_y      = 0;

      // Apply configuration to the panel instance.
      _panel_instance.config(cfg);
    }

    // Set the RGB bus and panel instances.
    _panel_instance.setBus(&_bus_instance);
    setPanel(&_panel_instance);
  }
};


LGFX lcd;

void onDataReady(uint32_t len) {
  Serial.printf("Received %d bytes\n", len);
  //print first two bytes
  //Serial.printf("First two bytes: %02X %02X\n", receive_buffer[0], receive_buffer[1]);
  if(!(receive_buffer[0]==0xFF && receive_buffer[1]==0xD8)){
    Serial.println("No JPG Header");
    return;
  };
 
 unsigned long timer = millis();
 
  if(!lcd.drawJpg(receive_buffer, len, 80, 0, 256, 192)){
    Serial.println("Error drawing jpg");
  }
  Serial.printf("Time taken: %d\n", millis() - timer);
  //file.close();
  
  
  Serial.println( "Drew JPG" );
  

  
}






/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{

  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  

  //lcd.fillScreen(TFT_WHITE);
#if (LV_COLOR_16_SWAP != 0)
 lcd.pushImageDMA(area->x1, area->y1, w, h,(lgfx::rgb565_t*)&color_p->full);
#else
  lcd.pushImageDMA(area->x1, area->y1, w, h,(lgfx::rgb565_t*)&color_p->full);//
#endif

  lv_disp_flush_ready(disp);

}


void setup() {
 // put your setup code here, to run once:
  Serial.begin(115200); // Init Display
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  if( !psramInit() ) {
    Serial.println("PSRAM FAIL");
  }
  
  receive_buffer = (uint8_t*)  ps_calloc(98358,sizeof( uint8_t ) ) ;
  radio.setRecvBuffer(receive_buffer);
  radio.setRecvCallback(onDataReady);

  radio.init();
  
  //print mac address
  lcd.init();
  lcd.setColorDepth(24);
  //lcd.begin();
  //lcd.fillScreen(TFT_MAGENTA);
  lcd.setTextSize(2);
  delay(200);

  //lv_init();
  //touch_init();
  

 

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);


  //ui_init();//Boot UI
  //start timer using millis()
  

  Serial.println("init done");

  File border=SPIFFS.open("/heart_border.png", "r");
  lcd.drawPng(&border,0,0,80,480);
  border.close();
  delay(1000);
  File border1=SPIFFS.open("/heart_border.png", "r");
  lcd.drawPng(&border1,720,0,80,480);
  border.close();
  




}

void loop() {
  //lv_timer_handler();
  delay(5);
}
