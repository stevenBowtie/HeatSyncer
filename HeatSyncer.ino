#include <Wire.h>
#include <SeeedOLED.h>
#include <TinyGPS.h>
#define SerialBaud   9600
#define Serial1Baud  9600

TinyGPS gps;
long lat, lon;
unsigned long fix_age, time, date, speed, course;
unsigned long chars;
unsigned short sentences, failed_checksum;

void setup(){
  Serial.begin(SerialBaud);
  Serial1.begin(Serial1Baud);
  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display
  DDRB|=0x21;        
  PORTB |= 0x21;

  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(3,4);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("HeatSyncer"); //Print the String
  delay(1000);
  SeeedOled.clearDisplay();
}

void loop(){
  if (Serial1.available()){
    if(gps.encode(Serial1.read())){
      gps.get_position(&lat, &lon, &fix_age);
      SeeedOled.setTextXY(0,0);
      SeeedOled.putString("Lat:");
      SeeedOled.setTextXY(0,7);
      SeeedOled.putNumber(lat);
      SeeedOled.setTextXY(1,0);
      SeeedOled.putString("Long:"); 
      SeeedOled.setTextXY(1,6);
      SeeedOled.putNumber(lon);
      Serial.println(lat);
      Serial.println(lon);
    }
 }
}
