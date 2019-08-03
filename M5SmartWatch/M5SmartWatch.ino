/*
    note: need follow libraries from library manager

    RTClib by Adafruit
    M5Stack SD-Updater by tobozo
*/

#include <M5Stack.h>
#include <M5StackUpdater.h>
#include "RTClib.h"

RTC_PCF8523 rtc;

char filler[] = "   ";

void startRTC() {
  if (!rtc.begin()) {
    printLog("Couldn't find RTC");
  }
  if (!rtc.initialized()) {
    printLog("RTC is not initialized.");

    // set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTIme(F(__DATE__), F(__TIME__)));
  }
}

void printLog(String message) {
  Serial.println(message);
  M5.Lcd.println(message);
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
  M5.Lcd.setTextSize(3);
}

void loop() {

  M5.Lcd.setCursor(0, 0);
 
  DateTime now = rtc.now();
    
  M5.Lcd.printf("Date:%d:%d:%d%s\n" , now.year(), now.month(), now.day(), filler);
  M5.Lcd.printf("Time:%d:%d:%d%s\n" , now.hour(), now.minute(), now.second(), filler);

  delay(1000);
}
