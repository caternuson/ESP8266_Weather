//================================================================
// esp8266_weather.ino
//
// Weather forecast display.
//
// Carter Nelson
// 2016-11-23
//================================================================
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <Adafruit_LEDBackpack.h>

#include "weather_config.h"
#include "led8x8icons.h"

String forecast[4];

//-----------
// The 8x8 LED Matrices
//-----------
Adafruit_8x8matrix matrix[4] = {
  Adafruit_8x8matrix() ,
  Adafruit_8x8matrix() ,
  Adafruit_8x8matrix() ,
  Adafruit_8x8matrix() ,  
};

//--------------------------------------------------------
// set_raw64
//
// Set specified matrix to bitmap defined by 64 bit value.
//--------------------------------------------------------
void set_raw64(uint64_t value, uint8_t m) {
  uint8_t row_byte, pixel_bit;
  for (int y=0; y<=7; y++) {
    row_byte = value >> (8*y);
    for (int x=0; x<=7; x++) {
      pixel_bit = row_byte >> x & 0x01;
      matrix[m].drawPixel(x, y, pixel_bit);
    }
  }
  matrix[m].writeDisplay();
}

//--------------------------------------------------------
// connect_to_wifi
//
// Establish connection to Wifi using credentials defined
// in weather_config.h
//--------------------------------------------------------
void connect_to_wifi() {
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(MY_SSID);
  WiFi.begin(MY_SSID, MY_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected. [ip addr ");  
  Serial.print(WiFi.localIP());
  Serial.println("]");
}

//--------------------------------------------------------
// get_noaa_forecast
//
// Get JSON formatted forecast for LAT/LON defined in
// weather_config.h
//--------------------------------------------------------
bool get_noaa_forecast() {
  DynamicJsonBuffer jsonBuffer;               
  HTTPClient http;
  
  String HOST = "forecast.weather.gov";
  String URL = String("/MapClick.php?lat=") +
               String(LAT) +
               String("&lon=") +
               String(LON) +
               String("&FcstType=json");

  http.begin(HOST, 80, URL);

  Serial.println("Getting forecast from:");
  Serial.println(HOST);
  Serial.println(URL);
  Serial.println("-------------------------");  
  
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    Serial.print("SIZE: ");
    Serial.println(http.getSize());
    JsonObject& root = jsonBuffer.parseObject(http.getString());
    if (!root.success()) {
      Serial.println("JSON ERROR.");
      return false;
    } else {
      Serial.println("JSON PARSED.");
      forecast[0] = String((const char*)root["data"]["weather"][0]);
      forecast[1] = String((const char*)root["data"]["weather"][2]);
      forecast[2] = String((const char*)root["data"]["weather"][4]);
      forecast[3] = String((const char*)root["data"]["weather"][6]);
      return true;
    }
  } else {
    Serial.print("HTTP ERROR: ");
    Serial.println(httpCode);
    return false;
  }

  http.end();   
}

//--------------------------------------------------------
// display_forecast
//
// Display the daily forecast.
//--------------------------------------------------------
void display_forecast() {
  for (int i=0; i<4; i++) {
    forecast[i].toUpperCase();
    if (forecast[i].indexOf("SUNNY") >= 0) {
      Serial.println("ICON_SUNNY");
    } else if (forecast[i].indexOf("RAIN") >= 0) {
      Serial.println("ICON_RAIN");
    } else if (forecast[i].indexOf("CLOUD") >= 0) {
      Serial.println("ICON_CLOUD");
    } else if (forecast[i].indexOf("SHOWERS") >= 0) {
      Serial.println("ICON_SHOWERS");
    } else if (forecast[i].indexOf("SNOW") >= 0) {
      Serial.println("ICON_SNOW");
    } else if (forecast[i].indexOf("STORM") >= 0) {
      Serial.println("ICON_STORM");
    }
  }  
}

//--------------------------------------------------------
//                S  E  T  U  P
//--------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("ESP8266 Weather Display");
    
  // Initialize 8x8 LED matrices
  matrix[0].begin(0x70);  // tens digit for hour
  matrix[1].begin(0x71);  // ones digit for hour
  matrix[2].begin(0x72);  // tens digit for minute
  matrix[3].begin(0x73);  // ones digit for minute

  // Connect to LAN via WiFi
  connect_to_wifi();

  // Get forecast
  if (get_noaa_forecast()) {
    // Display forecast
    display_forecast();
  }
}

//--------------------------------------------------------
//                    L  O  O  P
//--------------------------------------------------------
void loop() {
  // TODO: add cron like sleep/delay or something...

  // debug
  set_raw64(ICON_SUNNY,0);
  delay(1000);
  set_raw64(ICON_CLOUD,0);
  delay(1000);
  set_raw64(ICON_STORM,0);
  delay(1000);
  set_raw64(ICON_RAIN,0);
  delay(1000);
}
