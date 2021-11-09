// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

RTC_DS1307 rtc;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (rs, e, d4, d5, d6, d7)

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri","Sat"};
int state = 0;
void setup () 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  //check if the RTC module is connected
  if (! rtc.begin()) 
  {
    lcd.print("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) 
  {
    lcd.print("RTC is NOT running!");
  }
  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));// to set the time manually 
  
}

void loop () 
{
    DateTime now = rtc.now();  //this line stores real time in DateTime now
    int getHour = now.hour();
    if(getHour >= 12){
      getHour = getHour - 12;
      state = 1;
      if(getHour == 0) getHour = 12;
    }
    lcd.setCursor(1, 1);
    lcd.print(getHour);
    lcd.print(':');
    lcd.print(now.minute());
    lcd.print(':');
    lcd.print(now.second());
    lcd.print("   ");
    if( state = 1){
      lcd.setCursor(10,1);
      lcd.print ("PM");
    }
    else {
      lcd.setCursor(10,1);
      lcd.print("AM");
    }

    lcd.setCursor(0, 0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(" ,");
    lcd.print(now.day());
    lcd.print('/');
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.year()); 
    
}


