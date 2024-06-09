#include <Arduino.h>
#include <lvgl.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <SPIFFS.h>
#include <SPI.h>
#include <ArduinoWebsockets.h>
using namespace websockets;

#define PWM_PIN_1 19         // PWM output pin
#define DIRECTION_PIN_1 20   // Direction control pin
#define PWM_PIN_2 38         // PWM output pin
#define DIRECTION_PIN_2 44   // Direction control pin
#define PWM_FREQUENCY 100000 // 100 kHz
#define PWM_RESOLUTION 8     // 8-bit resolution
#define PWM_CHANNEL_1 0      // PWM channel
#define PWM_CHANNEL_2 2      // PWM channel
#define SWITCH_INTERVAL 5000 // Interval to change direction in milliseconds
int direction = HIGH;        // Initial direction state

WebsocketsClient client;
// Set your access point network credentials
const char *ssid = "Graham-ESP32";
const char *password = "123456789";

uint8_t movement = 4;
TaskHandle_t Task1;

SPIClass &spi = SPI;

int i = 0;
// #include <Arduino_GFX_Library.h>
#define TFT_BL 2
// Define a class named LGFX, inheriting from the LGFX_Device class.
class LGFX : public lgfx::LGFX_Device
{
public:
  // Instances for the RGB bus and panel.
  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_RGB _panel_instance;

  // Constructor for the LGFX class.
  LGFX(void)
  {
    // Configure the RGB bus.
    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;

      // Configure data pins.
      cfg.pin_d0 = GPIO_NUM_15; // B0
      cfg.pin_d1 = GPIO_NUM_7;  // B1
      cfg.pin_d2 = GPIO_NUM_6;  // B2
      cfg.pin_d3 = GPIO_NUM_5;  // B3
      cfg.pin_d4 = GPIO_NUM_4;  // B4

      cfg.pin_d5 = GPIO_NUM_9;  // G0
      cfg.pin_d6 = GPIO_NUM_46; // G1
      cfg.pin_d7 = GPIO_NUM_3;  // G2
      cfg.pin_d8 = GPIO_NUM_8;  // G3
      cfg.pin_d9 = GPIO_NUM_16; // G4
      cfg.pin_d10 = GPIO_NUM_1; // G5

      cfg.pin_d11 = GPIO_NUM_14; // R0
      cfg.pin_d12 = GPIO_NUM_21; // R1
      cfg.pin_d13 = GPIO_NUM_47; // R2
      cfg.pin_d14 = GPIO_NUM_48; // R3
      cfg.pin_d15 = GPIO_NUM_45; // R4

      // Configure sync and clock pins.
      cfg.pin_henable = GPIO_NUM_41;
      cfg.pin_vsync = GPIO_NUM_40;
      cfg.pin_hsync = GPIO_NUM_39;
      cfg.pin_pclk = GPIO_NUM_0;
      cfg.freq_write = 15000000;

      // Configure timing parameters for horizontal and vertical sync.
      cfg.hsync_polarity = 0;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 48;
      cfg.hsync_back_porch = 40;

      cfg.vsync_polarity = 0;
      cfg.vsync_front_porch = 1;
      cfg.vsync_pulse_width = 31;
      cfg.vsync_back_porch = 13;

      // Configure polarity for clock and data transmission.
      cfg.pclk_active_neg = 1;
      cfg.de_idle_high = 0;
      cfg.pclk_idle_high = 0;

      // Apply configuration to the RGB bus instance.
      _bus_instance.config(cfg);
    }

    // Configure the panel.
    {
      auto cfg = _panel_instance.config();
      cfg.memory_width = 800;
      cfg.memory_height = 480;
      cfg.panel_width = 800;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;

      // Apply configuration to the panel instance.
      _panel_instance.config(cfg);
    }

    // Set the RGB bus and panel instances.
    _panel_instance.setBus(&_bus_instance);
    setPanel(&_panel_instance);
  }
};

LGFX lcd;

void onMessageCallback(WebsocketsMessage message)
{
  Serial.printf("Received %d bytes\n", message.length());

  // received movement direction
  if (message.length() == 1)
  {
    Serial.printf("New Direction: %x\n", message.rawData().data()[0]);
    movement = message.rawData().data()[0];
    return;
  }
  // received JPG image
  else
  {
    auto data = message.rawData().data();
    // print first two bytes
    // Serial.printf("First two bytes: %02X %02X\n", receive_buffer[0], receive_buffer[1]);
    if (!(data[0] == 0xFF && data[1] == 0xD8))
    {
      Serial.println("No JPG Header");
      return;
    };

    unsigned long timer = millis();

    if (!lcd.drawJpg((uint8_t *)data, message.length(), 80, 0, 256, 192))
    {
      Serial.println("Error drawing jpg");
    }
    Serial.printf("Draw time: %d\n", millis() - timer);
    // file.close();

    Serial.println("Drew JPG");
  }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
  if (event == WebsocketsEvent::ConnectionOpened)
  {
    Serial.println("Connnection Opened");
  }
  else if (event == WebsocketsEvent::ConnectionClosed)
  {
    Serial.println("Connnection Closed");
  }
  else if (event == WebsocketsEvent::GotPing)
  {
    Serial.println("Got a Ping!");
  }
  else if (event == WebsocketsEvent::GotPong)
  {
    Serial.println("Got a Pong!");
  }
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{

  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  // lcd.fillScreen(TFT_WHITE);
#if (LV_COLOR_16_SWAP != 0)
  lcd.pushImageDMA(area->x1, area->y1, w, h, (lgfx::rgb565_t *)&color_p->full);
#else
  lcd.pushImageDMA(area->x1, area->y1, w, h, (lgfx::rgb565_t *)&color_p->full); //
#endif

  lv_disp_flush_ready(disp);
}
// motor control loop running on core 0
void Task1code(void *pvParameters)
{
  for (;;)
  {
    // forward movement
    if (movement == 1)
    {
      direction = LOW;
      ledcWrite(PWM_CHANNEL_1, 255);
      ledcWrite(PWM_CHANNEL_2, 255); // dir low
      // contract
      digitalWrite(DIRECTION_PIN_1, direction);  // low makes right motor turn cw
      digitalWrite(DIRECTION_PIN_2, !direction); // high makes left motor turn ccw
      delay(1000);
      // expand
      direction = !direction;
      digitalWrite(DIRECTION_PIN_1, direction);
      digitalWrite(DIRECTION_PIN_2, !direction);
      delay(300);
    }
    // left movement
    else if (movement == 2)
    {
      direction = LOW;
      ledcWrite(PWM_CHANNEL_1, 255);
      ledcWrite(PWM_CHANNEL_2, 200); // dir low
      // contract
      digitalWrite(DIRECTION_PIN_1, direction);  // low makes right motor turn cw
      digitalWrite(DIRECTION_PIN_2, !direction); // high makes left motor turn ccw
      delay(1000);
      // expand
      direction = !direction;
      digitalWrite(DIRECTION_PIN_1, direction);
      digitalWrite(DIRECTION_PIN_2, !direction);
      delay(300);
    }
    // right movement
    else if (movement == 3)
    {
      direction = LOW;
      ledcWrite(PWM_CHANNEL_1, 200);
      ledcWrite(PWM_CHANNEL_2, 255); // dir low
      // contract
      digitalWrite(DIRECTION_PIN_1, direction);  // low makes right motor turn cw
      digitalWrite(DIRECTION_PIN_2, !direction); // high makes left motor turn ccw
      delay(1000);
      // expand
      direction = !direction;
      digitalWrite(DIRECTION_PIN_1, direction);
      digitalWrite(DIRECTION_PIN_2, !direction);
      delay(300);
    }
    else if (movement == 4)
    {
      ledcWrite(PWM_CHANNEL_1, 0);
      ledcWrite(PWM_CHANNEL_2, 0);
    }
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Init Display
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  if (!psramInit())
  {
    Serial.println("PSRAM FAIL");
  }
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.printf("IP address: %s\n", IP.toString().c_str());

  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);

  lcd.init();
  lcd.setColorDepth(24);
  lcd.setTextSize(2);
  delay(200);


  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  Serial.println("init done");

  File border = SPIFFS.open("/heart_border.png", "r");
  lcd.drawPng(&border, 0, 0, 80, 480);
  border.close();
  delay(1000);
  File border1 = SPIFFS.open("/heart_border.png", "r");
  lcd.drawPng(&border1, 720, 0, 80, 480);
  border.close();

  // motor setup
  //  Initialize the PWM pin and channel
  ledcSetup(PWM_CHANNEL_1, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN_1, PWM_CHANNEL_1);
  ledcAttachPin(PWM_PIN_2, PWM_CHANNEL_2);

  // Start the PWM with 50% duty cycle
  ledcWrite(PWM_CHANNEL_1, 255); // 50% of 255 (8-bit resolution)
  ledcWrite(PWM_CHANNEL_2, 255);

  // Initialize the direction pin
  pinMode(DIRECTION_PIN_1, OUTPUT);
  digitalWrite(DIRECTION_PIN_1, direction);
  pinMode(DIRECTION_PIN_2, OUTPUT);
  digitalWrite(DIRECTION_PIN_2, direction);

  xTaskCreatePinnedToCore(
      Task1code, /* Task function. */
      "Task1",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      0,         /* priority of the task */
      &Task1,    /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */
}
// runs on Core 1
void loop()
{
  while (WiFi.softAPgetStationNum() < 1)
  {
    Serial.println("Waiting for WiFi connection");
    delay(1000);
  }
  if (!client.available())
  {
    Serial.println("Waiting for client");
    client.connect("192.168.4.2", 81, "/");
  }
  client.poll();
}
