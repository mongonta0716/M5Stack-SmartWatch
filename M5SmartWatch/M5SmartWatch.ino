/*
    note: need follow libraries from library manager

    RTClib by Adafruit
    M5Stack SD-Updater by tobozo
*/

#include <M5Stack.h>
#include <M5StackUpdater.h>
#include "RTClib.h"
#include <time.h>
#include <WiFi.h>

char ntpServer[] = "ntp.jst.mfeed.ad.jp";
const long gmtOffset_sec = 9 * 3600;
const int  daylightOffset_sec = 0;
struct tm timeinfo;


RTC_PCF8523 rtc;

char filler[] = "   ";

void startRTC() {
  if (!rtc.begin()) {
    printLog("Couldn't find RTC");
  }
  if (!rtc.initialized()) {
    printLog("RTC is not initialized.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  DateTime now = rtc.now();
  if (now.hour() > 24) {
    printLog("RTC data is incorrect.");
  }
  
}

void printLog(String message) {
  Serial.println(message);
  M5.Lcd.println(message);
}

void adjustRTCfromNTP() {
  WiFi.begin();
  M5.Lcd.setCursor(0, 200);
  while (WiFi.status() != WL_CONNECTED) {
    M5.Lcd.print(".");
    delay(500);
  }
  M5.Lcd.println("WiFi connected");
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  M5.Lcd.setCursor(0, 200);
  M5.Lcd.print("Get Time");
  while (!getLocalTime(&timeinfo)) {
    M5.Lcd.print(".");
    delay(1000);
  }
  M5.Lcd.setCursor(0, 200);
  M5.Lcd.print("RTC adjusted     ");
  rtc.adjust(DateTime((int)(timeinfo.tm_year + 1900),
                      (int)(timeinfo.tm_mon + 1),
                      (int)timeinfo.tm_mday,
                      (int)timeinfo.tm_hour,
                      (int)timeinfo.tm_min,
                      (int)timeinfo.tm_sec));
  WiFi.disconnect();

}

void printLocalTime() {
  getLocalTime(&timeinfo);
  String dateStr = (String)(timeinfo.tm_year + 1900)
          + "/" + (String)(timeinfo.tm_mon + 1)
          + "/" + (String)timeinfo.tm_mday;
  String timeStr = (String)timeinfo.tm_hour
          + ":" + (String)timeinfo.tm_min
          + ":" + (String)timeinfo.tm_sec;
  M5.Lcd.println("LocalTime");
  M5.Lcd.println(dateStr + filler);
  M5.Lcd.println(timeStr + filler);
}

void setup() {
  M5.begin();
  Wire.begin();
  if(digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
  M5.Lcd.setBrightness(10);

  startRTC();

  M5.Lcd.clear(BLACK);

  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(0, 0);
 
  DateTime now = rtc.now();
  M5.Lcd.println("M5SmartWatch");
  M5.Lcd.printf("\nDate:%d:%d:%d%s\n" , now.year(), now.month(), now.day(), filler);
  M5.Lcd.printf("Time:%d:%d:%d%s\n" , now.hour(), now.minute(), now.second(), filler);
//  printLocalTime();
//  M5.Lcd.println("");
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("\nBtnA:Adjust RTC from NTP");

  if (M5.BtnA.wasPressed()) {
    adjustRTCfromNTP();
  }

  delay(10);
}
