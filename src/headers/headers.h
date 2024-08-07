#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLBNwjHSv1"
#define BLYNK_TEMPLATE_NAME "iot"
#define BLYNK_AUTH_TOKEN "m7YWUPmMqkCWHNBL9ut7NhyLBQ-9eR_y"

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <BlynkSimpleEsp32_SSL.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <time.h>

// SD Card Server Headers 
// #include <SD.h>
// #include <SPIFFS.h>


// Defining MCU Pins 
#define MCU_1 23
#define MCU_2 5
#define MCU_3 18
#define MCU_4 19
#define BUZZER 2
#define sw_a 22
#define sw_b 23

Adafruit_SSD1306 display(128, 64, &Wire, -1); 


#define DHTPIN 4          // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);


BlynkTimer timer;
BlynkTimer t_timer;
BlynkTimer logger_timer;



// WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Cloud9";
char pass[] = "khliansp";

// Time Credentials
const char* ntpServer = "time.google.com";
const long  gmtOffset_sec = 21600;
const int   daylightOffset_sec = 0;