#include <headers/headers.h>
#include <logos/boot.h>
#include <logos/somoy.h>
#include <logos/ok_conn.h>

<<<<<<< HEAD
// Write to Blynk String 
=======
// Write to Blynk String
>>>>>>> 5bdd953 (updated.)
void cblynk(String msg)
{
  Blynk.virtualWrite(V0, msg);
}

void lcdWr(int x, int y, int ts, String m)
{
  display.clearDisplay();
  display.setTextSize(ts);
<<<<<<< HEAD
  display.setCursor(x,y);
=======
  display.setCursor(x, y);
>>>>>>> 5bdd953 (updated.)
  display.print(m);
  display.display();
}

// Modified lcd_i2c function
<<<<<<< HEAD
void lcd_i2c(int x, int y, String m) {
  static String previousMessages[4] = {"", "", "", ""};  // Adjust the array size based on your display
=======
void lcd_i2c(int x, int y, String m)
{
  static String previousMessages[4] = {"", "", "", ""}; // Adjust the array size based on your display
>>>>>>> 5bdd953 (updated.)

  // Set cursor to the position
  lcd.setCursor(x, y);

  // If the message is different from the previous one, update the display
<<<<<<< HEAD
  if (previousMessages[y] != m) {
=======
  if (previousMessages[y] != m)
  {
>>>>>>> 5bdd953 (updated.)
    lcd.print("                "); // Clear the previous message (Assuming 16 characters wide display)
    lcd.setCursor(x, y);
    lcd.print(m);

    // Update the previous message
    previousMessages[y] = m;
  }
}

<<<<<<< HEAD

=======
>>>>>>> 5bdd953 (updated.)
// This function sends Arduino's up time every second to Virtual Pin (5) and shows it to the OLED Display
void sendSensor()
{
  // delay(2000);

<<<<<<< HEAD
  //read temperature and humidity
  float t = dht.readTemperature();

  if (isnan(t)) 
=======
  // read temperature and humidity
  float t = dht.readTemperature();

  if (isnan(t))
>>>>>>> 5bdd953 (updated.)
  {
    Blynk.virtualWrite(V5, 0);
    return;
  }
<<<<<<< HEAD
  else 
=======
  else
>>>>>>> 5bdd953 (updated.)
  {
    Blynk.virtualWrite(V5, t);
    return;
  }
}

// print TIme to OLED
void printLocalTime()
{
  struct tm timeinfo;
<<<<<<< HEAD
  if(!getLocalTime(&timeinfo)){
=======
  if (!getLocalTime(&timeinfo))
  {
>>>>>>> 5bdd953 (updated.)
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
<<<<<<< HEAD
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
  float t = dht.readTemperature();
  
  
  //Display Time
  display.setCursor(5,5);

  if (ssint%2==0)
  {
    // lcd.clear();
    lcd_i2c(0,0,""+String(timeWeekDay)+"");
    lcd_i2c(0,1,""+String(dddd)+" "+String(mmmm)+" "+String(yyyy)+"");
    lcd_i2c(0,2,""+String(hh)+":"+String(mm)+":"+String(ss)+"");
    lcd_i2c(0,3,"Temp: "+String(t)+" C");
    // bigNumberLCD.print(""+String(hh)+":"+String(mm)+":"+String(ss)+"");
  }
  else 
  {
    // lcd.clear();
    lcd_i2c(0,0,""+String(timeWeekDay)+"");
    lcd_i2c(0,1,""+String(dddd)+" "+String(mmmm)+" "+String(yyyy)+"");
    lcd_i2c(0,2,""+String(hh)+" "+String(mm)+" "+String(ss)+"");
    lcd_i2c(0,3,"Temp: "+String(t)+" C");
  }

  

  // if ((ssint > 33) || (ssint < 30))
  // {

    // display.setTextSize(2);
    // display.print(""+String(timeWeekDay)+"");
    // display.setCursor(5,25);
    // display.setTextSize(1);
    // display.print(""+String(dddd)+" "+String(mmmm)+" "+String(yyyy)+"");
    // display.setCursor(5,45);
    // display.setTextSize(2);
    // if (ssint%2==0)
    // {
    //   display.print(""+String(hh)+":"+String(mm)+":"+String(ss)+"");
    //   display.drawRoundRect(1,1,126,62,5,WHITE);
    // }
    // else 
    // {
    //   display.print(""+String(hh)+" "+String(mm)+" "+String(ss)+"");
    //   display.drawRoundRect(1,1,126,64,5,BLACK);

    // }
    // display.display();


    
  // }
  
=======
  strftime(hh, 3, "%I", &timeinfo);
  strftime(mm, 3, "%M", &timeinfo);
  strftime(ss, 3, "%S", &timeinfo);
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  strftime(dddd, 3, "%d", &timeinfo);
  strftime(mmmm, 10, "%B", &timeinfo);
  strftime(yyyy, 10, "%Y", &timeinfo);
  int ssint = atoi(ss);

  // Clear Display
  display.clearDisplay();
  float t = dht.readTemperature();

  // Display Time
  display.setCursor(5, 5);

  if (ssint % 2 == 0)
  {
    // lcd.clear();
    lcd_i2c(0, 0, "" + String(timeWeekDay) + "");
    lcd_i2c(0, 1, "" + String(dddd) + " " + String(mmmm) + " " + String(yyyy) + "");
    lcd_i2c(0, 2, "" + String(hh) + ":" + String(mm) + ":" + String(ss) + "");
    lcd_i2c(0, 3, "Temp: " + String(t) + " C");
    // bigNumberLCD.print(""+String(hh)+":"+String(mm)+":"+String(ss)+"");
  }
  else
  {
    // lcd.clear();
    lcd_i2c(0, 0, "" + String(timeWeekDay) + "");
    lcd_i2c(0, 1, "" + String(dddd) + " " + String(mmmm) + " " + String(yyyy) + "");
    lcd_i2c(0, 2, "" + String(hh) + " " + String(mm) + " " + String(ss) + "");
    lcd_i2c(0, 3, "Temp: " + String(t) + " C");
  }

  // if ((ssint > 33) || (ssint < 30))
  // {

  // display.setTextSize(2);
  // display.print(""+String(timeWeekDay)+"");
  // display.setCursor(5,25);
  // display.setTextSize(1);
  // display.print(""+String(dddd)+" "+String(mmmm)+" "+String(yyyy)+"");
  // display.setCursor(5,45);
  // display.setTextSize(2);
  // if (ssint%2==0)
  // {
  //   display.print(""+String(hh)+":"+String(mm)+":"+String(ss)+"");
  //   display.drawRoundRect(1,1,126,62,5,WHITE);
  // }
  // else
  // {
  //   display.print(""+String(hh)+" "+String(mm)+" "+String(ss)+"");
  //   display.drawRoundRect(1,1,126,64,5,BLACK);

  // }
  // display.display();

  // }
>>>>>>> 5bdd953 (updated.)
}

// Blynk App write listeners
// Get the previous states of the pins
BLYNK_CONNECTED()
{
  display.clearDisplay();
  // lcdWr(30,30,1,"Syncing...");
  lcd.print("Syncing time...");
<<<<<<< HEAD
  Blynk.syncAll();  
=======
  Blynk.syncAll();
>>>>>>> 5bdd953 (updated.)
  display.clearDisplay();
  // Start the time sync
  t_timer.setInterval(1000L, printLocalTime);
  cblynk(".::' ----------------- '::.");
  cblynk(".::' SCADA Server by Afif, Copyright: Mashrur Mohsin Afif. '::.");
  cblynk("[i] Synchronized to server values.");
}
// LIGHT @ V1
BLYNK_WRITE(V1)
{
<<<<<<< HEAD
  int pinValue = param.asInt(); 
  Serial.print("HOME SCADA V1: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 1: "+String(pinValue)+"");
  Serial.println(pinValue);
  digitalWrite(BUZZER,pinValue);
=======
  int pinValue = param.asInt();
  Serial.print("HOME SCADA V1: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 1: " + String(pinValue) + "");
  Serial.println(pinValue);
  digitalWrite(BUZZER, pinValue);
>>>>>>> 5bdd953 (updated.)
}

// LIGHT @ V2
BLYNK_WRITE(V2)
{
<<<<<<< HEAD
  int pinValue = param.asInt(); 
  Serial.print("HOME SCADA V2: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 2: "+String(pinValue)+"");
  Serial.println(pinValue);
  digitalWrite(MCU_2,!pinValue);
=======
  int pinValue = param.asInt();
  Serial.print("HOME SCADA V2: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 2: " + String(pinValue) + "");
  Serial.println(pinValue);
  digitalWrite(MCU_2, !pinValue);
>>>>>>> 5bdd953 (updated.)
}

// LIGHT @ V3
BLYNK_WRITE(V3)
{
<<<<<<< HEAD
  int pinValue = param.asInt(); 
  Serial.print("HOME SCADA V3: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 3: "+String(pinValue)+"");
  Serial.println(pinValue);
  digitalWrite(MCU_3,!pinValue);
=======
  int pinValue = param.asInt();
  Serial.print("HOME SCADA V3: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 3: " + String(pinValue) + "");
  Serial.println(pinValue);
  digitalWrite(MCU_3, !pinValue);
>>>>>>> 5bdd953 (updated.)
}

// LIGHT @ V4
BLYNK_WRITE(V4)
{
<<<<<<< HEAD
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
    cblynk("MAC address: "+WiFi.BSSIDstr()+"");
  }
  else if (cmd=="/device reboot")
  {
    cblynk("Rebooting device in 5 seconds...");
    for (int x=5;x>=1;x--)
    {
      delay(1000*x);
      cblynk("Time remaining: "+String(x)+" second(s).");
      if (x==1)
=======
  int pinValue = param.asInt();
  Serial.print("HOME SCADA V4: ");
  cblynk("[i] SCADA_CMD: APPLIANCE 4: " + String(pinValue) + "");
  Serial.println(pinValue);
  digitalWrite(MCU_4, !pinValue);
}

// For over the internet terminal thing
BLYNK_WRITE(V0)
{
  // read temperature and humidity
  float t = dht.readTemperature();
  String cmd = param.asString();
  Serial.print("[i] Got command: " + cmd + "");

  if (cmd == "/device mac")
  {
    cblynk("MAC address: " + WiFi.BSSIDstr() + "");
  }
  else if (cmd == "/device reboot")
  {
    cblynk("Rebooting device in 5 seconds...");
    for (int x = 5; x >= 1; x--)
    {
      delay(1000 * x);
      cblynk("Time remaining: " + String(x) + " second(s).");
      if (x == 1)
>>>>>>> 5bdd953 (updated.)
      {
        ESP.restart();
      }
    }
  }
<<<<<<< HEAD
  else if (cmd=="/t")
  {
    cblynk("Temperature: "+String(t)+" degree Celsius.");
  }
  else if (cmd=="/h")
  {
    cblynk("Humidity sensor is disabled.");
  }
  else if (cmd=="/wifi ip")
  {
    cblynk("WiFi Local address: "+WiFi.localIP().toString()+"");
  }
  else if (cmd=="/wifi strength")
  {
    cblynk("WiFi RSSI: "+String(WiFi.RSSI())+" dB");
  }
  else if (cmd=="/help")
  {
    cblynk("List of available commands:\n /device mac: Shows MAC address of the device. \n /device reboot: Reboots the device in 5 seconds. \n /temp : Shows temperature recorded in degree Celsius. \n /humidity : Shows humidity in percentage. \n /wifi ip : Shows local IP address of the device. \n /wifi strength: Shows the WiFi strength in dB.");
  }
  else if (cmd=="/memory")
  {
    cblynk("Free memory: "+String(ESP.getFreeHeap())+"");
  }
  else 
=======
  else if (cmd == "/t")
  {
    cblynk("Temperature: " + String(t) + " degree Celsius.");
  }
  else if (cmd == "/h")
  {
    cblynk("Humidity sensor is disabled.");
  }
  else if (cmd == "/wifi ip")
  {
    cblynk("WiFi Local address: " + WiFi.localIP().toString() + "");
  }
  else if (cmd == "/wifi strength")
  {
    cblynk("WiFi RSSI: " + String(WiFi.RSSI()) + " dB");
  }
  else if (cmd == "/help")
  {
    cblynk("List of available commands:\n /device mac: Shows MAC address of the device. \n /device reboot: Reboots the device in 5 seconds. \n /temp : Shows temperature recorded in degree Celsius. \n /humidity : Shows humidity in percentage. \n /wifi ip : Shows local IP address of the device. \n /wifi strength: Shows the WiFi strength in dB.");
  }
  else if (cmd == "/memory")
  {
    cblynk("Free memory: " + String(ESP.getFreeHeap()) + "");
  }
  else
>>>>>>> 5bdd953 (updated.)
  {
    cblynk("Invalid command, send /help for a list of available commands.");
  }
}

<<<<<<< HEAD

void setup() {
=======
void setup()
{
>>>>>>> 5bdd953 (updated.)
  // Begin Serial
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  // Setting the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
<<<<<<< HEAD
  // LCD Code 
  pinMode(LED_BUILTIN,OUTPUT);
  // pinMode Declaration
  pinMode(MCU_1,OUTPUT);
  pinMode(MCU_2,OUTPUT);
  pinMode(MCU_3,OUTPUT);
  pinMode(MCU_4,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  // For push Buttons

=======
  // LCD Code
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode Declaration
  pinMode(MCU_1, OUTPUT);
  pinMode(MCU_2, OUTPUT);
  pinMode(MCU_3, OUTPUT);
  pinMode(MCU_4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  // For Async Delay
  samplingInterval.start(2000, AsyncDelay::MILLIS);
>>>>>>> 5bdd953 (updated.)

  dht.begin();
  initSD();

<<<<<<< HEAD
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
=======
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
>>>>>>> 5bdd953 (updated.)
  }
  delay(10);
  display.clearDisplay();
  display.setTextColor(WHITE);
<<<<<<< HEAD
  display.setCursor(30,30);
  display.setTextSize(2);
  // display.drawBitmap
  display.print("Hello!");
  display.display();

  

=======
  display.setCursor(30, 30);
  display.setTextSize(2);
  // display.drawBitmap
  display.print("[...]");
  display.display();

>>>>>>> 5bdd953 (updated.)
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensor);

<<<<<<< HEAD

  



  // check_if_folders_exists();
  cblynk("[i] Connected to server.");
  cblynk("[i] LOCAL_IP: "+WiFi.localIP().toString()+"");
  cblynk("[i] MAC_ADDRESS: "+WiFi.BSSIDstr()+"");
  cblynk("[i] FTP Server Status: OKAY, Running.");
}

void loop() {
=======
  // check_if_folders_exists();
  cblynk("[i] Connected to server.");
  cblynk("[i] LOCAL_IP: " + WiFi.localIP().toString() + "");
  cblynk("[i] MAC_ADDRESS: " + WiFi.BSSIDstr() + "");
  cblynk("[i] FTP Server Status: OKAY, Running.");
}

void loop()
{
>>>>>>> 5bdd953 (updated.)
  Blynk.run();
  // runs BlynkTimer
  timer.run();
  // Time's timer
  t_timer.run();
  // Listen to PUSH BUTTONS
<<<<<<< HEAD
  
=======
>>>>>>> 5bdd953 (updated.)
}