#include <headers/headers.h>
// Write to Blynk String 
void cblynk(String msg)
{
  Blynk.virtualWrite(V0, msg);
}


void lcdWr(int x, int y, int ts, String m)
{
  display.clearDisplay();
  display.setTextSize(ts);
  display.setCursor(x,y);
  display.print(m);
  display.display();
}


// This function sends Arduino's up time every second to Virtual Pin (5) and shows it to the OLED Display
void sendSensor()
{
  // delay(2000);

  //read temperature and humidity
  float t = dht.readTemperature();

  if (isnan(t)) 
  {
    Blynk.virtualWrite(V5, 0);
    return;
  }
  else 
  {
    Blynk.virtualWrite(V5, t);
    return;
  }


}

// print TIme to OLED
void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  char hh[3];
  char mm[3];
  char ss[3];
  char timeWeekDay[10];
  char dddd[3];
  char mmmm[10];
  char yyyy[5];
  strftime(hh,3, "%I", &timeinfo);
  strftime(mm,3, "%M", &timeinfo);
  strftime(ss,3, "%S", &timeinfo);
  strftime(timeWeekDay,10, "%A", &timeinfo);
  strftime(dddd,3, "%d", &timeinfo);
  strftime(mmmm,10, "%B", &timeinfo);
  strftime(yyyy,10, "%Y", &timeinfo);
  int ssint = atoi(ss);
  

  //Clear Display
  display.clearDisplay();
  
  //Display Time
  display.setCursor(0,0);

  if ((ssint > 33) || (ssint < 30))
  {
    display.setTextSize(2);
    display.print(""+String(timeWeekDay)+"");
    display.setCursor(0,25);
    display.setTextSize(1);
    display.print(""+String(dddd)+" "+String(mmmm)+" "+String(yyyy)+"");
    display.setCursor(0,50);
    display.setTextSize(2);
    display.print(""+String(hh)+":"+String(mm)+":"+String(ss)+"");
    display.display();

  }
  else
  {
    //read temperature and humidity
    float t = dht.readTemperature();
    //Clear Display
    display.clearDisplay();
    
    //Display Temperature
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Temperature: ");
    display.setTextSize(2);
    display.setCursor(0,10);
    display.print(t);
    display.print(" ");
    display.setTextSize(1);
    display.cp437(true);
    display.write(167);
    display.setTextSize(2);
    display.print("C");
    display.display();
  }


}


// Check if pre-defined folders exist
void check_if_folders_exists()
{
  // Check /events 
  if (!SD.exists("/events"))
  {
    Serial.println("[i] Creating: /events");
  }
  else if (!SD.exists("/sensor_logs"))
  {
    Serial.println("[i] Creating: /sensor_logs");
  }
  else 
  {
    Serial.println("[i] Folder Checks: PASSED, OK");
  }
}
// Write data to SD Card
void wrdata(String folderName,String filename,String datatext)
{

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  char hh[3];
  char mm[3];
  char ss[3];
  char timeWeekDay[10];
  char dddd[3];
  char mmmm[10];
  char yyyy[5];
  strftime(hh,3, "%I", &timeinfo);
  strftime(mm,3, "%M", &timeinfo);
  strftime(ss,3, "%S", &timeinfo);
  strftime(timeWeekDay,10, "%A", &timeinfo);
  strftime(dddd,3, "%d", &timeinfo);
  strftime(mmmm,10, "%B", &timeinfo);
  strftime(yyyy,10, "%Y", &timeinfo);


  
  File testFile = SD.open("/"+folderName+"/"+filename+"", FILE_APPEND);
  if (testFile) 
  {
    // String data_text = ""+dddd+"/"+mmmm+"/"+yyyy+","+hh+":"+mm+":"+ss+","+datatext+"";
    testFile.print(dddd);
    testFile.print("-");
    testFile.print(mmmm);
    testFile.print("-");
    testFile.print(yyyy);
    testFile.print(",");
    testFile.print(hh);
    testFile.print(":");
    testFile.print(mm);
    testFile.print(":");
    testFile.print(ss);
    testFile.print(",");
    testFile.print(datatext);
    testFile.println(";");
    testFile.close();
    Serial.println("[i] Success, data written to /"+filename+"");
  } 
  else 
  {
    Serial.println("[x] Error, couldn't not open /"+filename+"");

  }
  
}

// Data logger for temp, humidity
void log_t_h()
{
  float t = dht.readTemperature();

  if (isnan(t)) 
  {
    return;
  }
  else 
  {
    wrdata("sensor_logs","temp_log.txt",""+String(t)+"");
    return;
  }

}




// Blynk App write listeners
// Get the previous states of the pins
BLYNK_CONNECTED()
{
  lcdWr(15,30,1,"Connected!");
  delay(1000);
  display.clearDisplay();
  Blynk.syncAll();  
  // Start the time sync
  t_timer.setInterval(1000L, printLocalTime);
  cblynk(".::' ----------------- '::.");
  cblynk(".::' SCADA Server by Afif, Copyright: Mashrur Mohsin Afif. '::.");
  cblynk("[i] Synchronized to server values.");
}
// LIGHT @ V1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); 
  Serial.print("HOME SCADA V1: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 1: "+String(pinValue)+"");
  Serial.println(pinValue);
  digitalWrite(BUZZER,!pinValue);

}

// LIGHT @ V2
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); 
  Serial.print("HOME SCADA V2: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 2: "+String(pinValue)+"");

  Serial.println(pinValue);
  digitalWrite(MCU_2,!pinValue);


}

// LIGHT @ V3
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); 
  Serial.print("HOME SCADA V3: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 3: "+String(pinValue)+"");
  Serial.println(pinValue);
  digitalWrite(MCU_3,!pinValue);


}

// LIGHT @ V4
BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); 
  Serial.print("HOME SCADA V4: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 4: "+String(pinValue)+"");
  Serial.println(pinValue);
  digitalWrite(MCU_4,!pinValue);

}

// For over the internet terminal thing 
BLYNK_WRITE(V0)
{
  //read temperature and humidity
  float t = dht.readTemperature();
  String cmd = param.asString(); 
  Serial.print("[i] Got command: "+cmd+"");

  if (cmd=="/device mac")
  {
    cblynk("MAC adress: "+WiFi.BSSIDstr()+"");
  }
  else if (cmd=="/device reboot")
  {
    cblynk("Rebooting device in 5 seconds...");
    for (int x=5;x>=1;x--)
    {
      delay(1000*x);
      cblynk("Time remaining: "+String(x)+" second(s).");
      if (x==1)
      {
        ESP.restart();
      }
    }
  }
  else if (cmd=="/t")
  {
    cblynk("Temperature: "+String(t)+" degree Celcius.");
  }
  else if (cmd=="/h")
  {
    cblynk("Humidity sensor is disabled.");
  }
  else if (cmd=="/wifi ip")
  {
    cblynk("WiFi Local adress: "+WiFi.localIP().toString()+"");
  }
  else if (cmd=="/wifi strength")
  {
    cblynk("WiFi RSSI: "+String(WiFi.RSSI())+" dB");
  }
  else if (cmd=="/wifi strength")
  {
    cblynk("WiFi RSSI: "+String(WiFi.RSSI())+" dB");
  }
  else if (cmd=="/help")
  {
    cblynk("List of available commands:\n /device mac: Shows MAC address of the device. \n /device reboot: Reboots the device in 5 seconds. \n /temp : Shows temperature recorded in degree Celcius. \n /humidity : Shows humidity in percentage. \n /wifi ip : Shows local IP address of the device. \n /wifi strength: Shows the WiFi strength in dB.");
  }
  else if (cmd=="/memory")
  {
    cblynk("Free memory: "+String(ESP.getFreeHeap())+"");
  }
  else if (cmd=="/cputemp")
  {
    
  }
  else if (cmd=="/memory")
  {
    cblynk("Free memory: "+String(ESP.getFreeHeap())+"");
  }
  else 
  {
    cblynk("Invalid command, send /help for a list of available commands.");
  }


}

void setup() {
  // Begin Serial
  Serial.begin(115200);


  // Setting the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // LCD Code 
  pinMode(LED_BUILTIN,OUTPUT);
  // pinMode Declaration
  pinMode(MCU_1,OUTPUT);
  pinMode(MCU_2,OUTPUT);
  pinMode(MCU_3,OUTPUT);
  pinMode(MCU_4,OUTPUT);
  pinMode(BUZZER,OUTPUT);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(15,30);
  // display.drawBitmap
  display.print("Connecting...");
  display.display();


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // printLocalTime();


  timer.setInterval(2000L, sendSensor);

  // Start server 
  #if defined(ESP32)
    SPIFFS.begin(true);
    // SPI.begin(14, 2, 15);
    if (!SD.begin(5)) {
      Serial.println("SD Card Mount Failed");
    }
  #elif defined(ESP8266)
    SPIFFS.begin();
  #endif



  check_if_folders_exists();
  cblynk("[i] Connected to server.");
  cblynk("[i] LOCAL_IP: "+WiFi.localIP().toString()+"");
  cblynk("[i] MAC_ADDRESS: "+WiFi.BSSIDstr()+"");
  cblynk("[i] FTP Server Status: OKAY, Running.");
  

  logger_timer.setInterval(60000L,log_t_h);

  

}

void loop() {
  Blynk.run();
  // runs BlynkTimer
  timer.run();
  // Time's timer
  t_timer.run();
  logger_timer.run();
  
}