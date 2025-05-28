// -------------------- BLYNK + DISPLAY IOT SYSTEM --------------------

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLBNwjHSv1"
#define BLYNK_TEMPLATE_NAME "iot"
#define BLYNK_AUTH_TOKEN "m7YWUPmMqkCWHNBL9ut7NhyLBQ-9eR_y"

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <WiFiClientSecure.h>
#include <BlynkSimpleEsp32_SSL.h>
#include <DHT.h>
#include <time.h>
#include <PushButton.h>

// -------------------- PINS & OBJECTS --------------------
#define MCU_1 23
#define MCU_2 5
#define MCU_3 18
#define MCU_4 19
#define BUZZER 2
#define DHTPIN 4
#define DHTTYPE DHT11
PushButton sw_a_pb(22);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer, t_timer, tt_timer;
char ssid[] = "Cloud9";
char pass[] = "khliansp";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 21600;
const int   daylightOffset_sec = 0;
bool timeLoaded = false;

bool states[4] = {false, false, false, false}; // V1-V4 states
const char* labels[4] = {"Buzzer", "L1", "L2", "L3"};
int changedIndex = -1;
bool newState = false;
unsigned long changeTimestamp = 0;

int blynkPing = -1;
unsigned long lastPingSent = 0;
unsigned long startMillis;
void printLocalTime();

// -------------------- CALLBACK HELPER --------------------
void cblynk(String msg) {
  Blynk.virtualWrite(V0, msg);
}

// -------------------- TERMINAL COMMANDS --------------------
BLYNK_WRITE(V0) {
  float t = dht.readTemperature();
  String cmd = param.asString();
  cmd.trim();

  Serial.println("[i] Got command: " + cmd);

  if (cmd == "/device mac") {
    cblynk("MAC address: " + WiFi.BSSIDstr());
  } 
  else if (cmd == "/device reboot") {
    cblynk("Rebooting device in 5 seconds...");
    for (int x = 5; x >= 1; x--) {
      delay(1000);
      cblynk("Time remaining: " + String(x) + " second(s).");
    }
    ESP.restart();
  } 
  else if (cmd == "/t") {
    cblynk("Temperature: " + String(t) + "°C");
  } 
  else if (cmd == "/wifi ip") {
    cblynk("WiFi Local IP: " + WiFi.localIP().toString());
  } 
  else if (cmd == "/wifi strength") {
    cblynk("WiFi RSSI: " + String(WiFi.RSSI()) + " dB");
  } 
  else if (cmd == "/memory") {
    cblynk("Free Heap: " + String(ESP.getFreeHeap()));
  } 
  else if (cmd == "/uptime") {
    unsigned long uptimeSec = (millis() - startMillis) / 1000;
    int hrs = uptimeSec / 3600;
    int mins = (uptimeSec % 3600) / 60;
    int secs = uptimeSec % 60;
    cblynk("Uptime: " + String(hrs) + "h " + String(mins) + "m " + String(secs) + "s");
  } 
  else if (cmd == "/status") {
    String res = "Relay Status:\n";
    for (int i = 0; i < 4; i++) {
      res += String(labels[i]) + ": " + (states[i] ? "ON" : "OFF") + "\n";
    }
    cblynk(res);
  } 
  else if (cmd == "/device info") {
    cblynk("ESP32 Chip Info:");
    cblynk("Cores: " + String(ESP.getChipCores()));
    cblynk("CPU Freq: " + String(ESP.getCpuFreqMHz()) + " MHz");
    cblynk("Flash Size: " + String(ESP.getFlashChipSize() / 1024.0 / 1024.0, 2) + " MB");
    cblynk("Sketch Size: " + String(ESP.getSketchSize() / 1024.0, 1) + " KB");
  }

  else if (cmd == "/relay toggle all") {
    for (int i = 0; i < 4; i++) {
      states[i] = !states[i];
      Blynk.virtualWrite(V1 + i, states[i]);
    }
    cblynk("All relays toggled.");
  }

  else if (cmd == "/relay off") {
    for (int i = 0; i < 4; i++) {
      states[i] = false;
      Blynk.virtualWrite(V1 + i, 0);
    }
    cblynk("All relays turned OFF.");
  }

  else if (cmd == "/relay on") {
    for (int i = 0; i < 4; i++) {
      states[i] = true;
      Blynk.virtualWrite(V1 + i, 1);
    }
    cblynk("All relays turned ON.");
  }

  else if (cmd == "/buzzer") {
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
    cblynk("Buzzer buzzed.");
  }

  else if (cmd == "/wifi reconnect") {
    cblynk("Reconnecting WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
  }

  else if (cmd == "/screen flash") {
    for (int i = 0; i < 3; i++) {
      u8g2.clear();
      u8g2.sendBuffer();
      delay(300);
      printLocalTime();
      delay(300);
    }
    cblynk("OLED flashed 3 times.");
  }

  else if (cmd == "/help") {
    cblynk("Commands:\n"
           "/device mac\n/device reboot\n/device info\n"
           "/t (temperature)\n/wifi ip\n/wifi strength\n/wifi reconnect\n"
           "/relay on\n/relay off\n/relay toggle all\n"
           "/buzzer\n/screen flash\n"
           "/memory\n/uptime\n/status\n/help");
  }

  else {
    cblynk("Invalid command. Type /help.");
  }
}

// -------------------- APPLIANCE CONTROL --------------------
BLYNK_WRITE(V1) { bool val = param.asInt(); if (val != states[0]) { states[0] = val; changedIndex = 0; newState = val; changeTimestamp = millis(); } }
BLYNK_WRITE(V2) { bool val = param.asInt(); if (val != states[1]) { states[1] = val; changedIndex = 1; newState = val; changeTimestamp = millis(); } }
BLYNK_WRITE(V3) { bool val = param.asInt(); if (val != states[2]) { states[2] = val; changedIndex = 2; newState = val; changeTimestamp = millis(); } }
BLYNK_WRITE(V4) { bool val = param.asInt(); if (val != states[3]) { states[3] = val; changedIndex = 3; newState = val; changeTimestamp = millis(); } }

// -------------------- PING --------------------
void sendPing() {
  lastPingSent = millis();
  Blynk.virtualWrite(V6, lastPingSent);
}
BLYNK_WRITE(V6) {
  unsigned long received = param.asInt();
  blynkPing = millis() - received;
}

// -------------------- SENSOR REPORT --------------------
void sendSensor() {
  float t = dht.readTemperature();
  Blynk.virtualWrite(V5, isnan(t) ? 0 : t);
}

// -------------------- LOADING SCREEN --------------------
void showLoadingScreen() {
  int frame = 0;
  while (!timeLoaded) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(10, 30, "Syncing Time...");
    const char* spinner[4] = {"-", "\\", "|", "/"};
    u8g2.drawStr(100, 50, spinner[frame % 4]);
    u8g2.sendBuffer();
    frame++;
    delay(100);
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) timeLoaded = true;
  }
}

// -------------------- TIME DISPLAY --------------------
void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  float temperature = dht.readTemperature();
  int second = timeinfo.tm_sec;
  int minute = timeinfo.tm_min;

  u8g2.clearBuffer();

  // Priority screen for 1500 ms after appliance change
  if (changedIndex != -1 && millis() - changeTimestamp < 1500) {
    u8g2.setFont(u8g2_font_fub17_tf);
    char topStr[20];
    sprintf(topStr, "%s %s", labels[changedIndex], newState ? "ON" : "OFF");
    int topW = u8g2.getStrWidth(topStr);
    u8g2.drawStr((128 - topW) / 2, 22, topStr);
  } else {
    changedIndex = -1;

    if (second == 35) {
      u8g2.setFont(u8g2_font_logisoso30_tf);
      char tempStr[10];
      sprintf(tempStr, "%.1f°C", temperature);
      int x = (128 - u8g2.getStrWidth(tempStr)) / 2;
      u8g2.drawStr(x, 40, tempStr);
    }
    else if (minute % 2 == 0 && second <= 3) {
      u8g2.setFont(u8g2_font_6x10_tf);
      char pingStr[20];
      sprintf(pingStr, "Ping: %s", (blynkPing >= 0) ? (String(blynkPing) + "ms").c_str() : "-- ms");
      u8g2.drawStr((128 - u8g2.getStrWidth(pingStr)) / 2, 30, pingStr);
      const char* status = Blynk.connected() ? "Blynk: Connected" : "Blynk: Disconnected";
      u8g2.drawStr((128 - u8g2.getStrWidth(status)) / 2, 44, status);
    } 
    else {
      char timeStr[16], weekdayStr[12], dateStr[32];
      strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
      strftime(weekdayStr, sizeof(weekdayStr), "%A", &timeinfo);
      strftime(dateStr, sizeof(dateStr), "%d %B %Y", &timeinfo);

      u8g2.setFont(u8g2_font_fub20_tf);
      u8g2.drawStr((128 - u8g2.getStrWidth(timeStr)) / 2, 28, timeStr);

      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.drawStr((128 - u8g2.getStrWidth(weekdayStr)) / 2, 42, weekdayStr);
      u8g2.drawStr((128 - u8g2.getStrWidth(dateStr)) / 2, 54, dateStr);
    }
  }

  // Always draw appliance box status
  if (changedIndex != -1 && millis() - changeTimestamp < 1500) {
    u8g2.setFont(u8g2_font_fub17_tf);
    char topStr[20];
    sprintf(topStr, "%s %s", labels[changedIndex], newState ? "ON" : "OFF");
    int topW = u8g2.getStrWidth(topStr);
    u8g2.drawStr((128 - topW) / 2, 22, topStr);

    // 👇 Draw bottom boxes ONLY when state has changed
    const int boxWidth = 28, boxHeight = 12, y = 50;
    u8g2.setFont(u8g2_font_6x10_tf);
    for (int i = 0; i < 4; i++) {
      int x = i * (boxWidth + 4);
      int lblW = u8g2.getStrWidth(labels[i]);
      u8g2.drawStr(x + (boxWidth - lblW) / 2, y - 4, labels[i]);
      u8g2.drawRFrame(x, y, boxWidth, boxHeight, 3);
      const char* status = states[i] ? "ON" : "OFF";
      int statusW = u8g2.getStrWidth(status);
      if (states[i]) {
        u8g2.drawRBox(x + 1, y + 1, boxWidth - 2, boxHeight - 2, 3);
        u8g2.setDrawColor(0);
        u8g2.drawStr(x + (boxWidth - statusW) / 2, y + 9, status);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(x + (boxWidth - statusW) / 2, y + 9, status);
      }
    }
  } else {
    changedIndex = -1;

    // 🕒 Proceed with time, temp, or ping screen as normal...
    // (your code already here)
  }


  u8g2.sendBuffer();
}

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(115200);
  u8g2.begin();
  dht.begin();
  sw_a_pb.setActiveLogic(LOW);

  pinMode(MCU_1, OUTPUT);
  pinMode(MCU_2, OUTPUT);
  pinMode(MCU_3, OUTPUT);
  pinMode(MCU_4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(22, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  showLoadingScreen();

  startMillis = millis();

  timer.setInterval(2000L, sendSensor);
  t_timer.setInterval(1000L, printLocalTime);
  tt_timer.setInterval(3000L, sendPing);
}

// -------------------- LOOP --------------------
void loop() {
  Blynk.run();
  timer.run();
  t_timer.run();
  tt_timer.run();
  sw_a_pb.update();
}
