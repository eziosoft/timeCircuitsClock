#include "RTClib.h"
//https://github.com/bremme/arduino-tm1637
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
#include "SevenSegmentFun.h"

RTC_DS3231 rtc;
DateTime now;

char data[4];//data buffer for sprinf

int backlightR = 30;
int backlightG = 100;
int backlightO = 30;

//RED Displays
const byte PIN_CLK_Red = A0;   // define CLK pin
const byte PIN_DIO_R1 = 12;
const byte PIN_DIO_R2 = 4;
const byte PIN_DIO_R3 = 5;

//GREEN Displays
const byte PIN_CLK_Green = A1;   // define CLK pin
const byte PIN_DIO_G1 = 6;
const byte PIN_DIO_G2 = 7;
const byte PIN_DIO_G3 = 8;

// ORANGE Displays
const byte PIN_CLK_Orange = A2;   // define CLK pin
const byte PIN_DIO_O1 = 9;   // define DIO pin (any digital pin)
const byte PIN_DIO_O2 = 10;
const byte PIN_DIO_O3 = 11;

SevenSegmentFun      green1(PIN_CLK_Green, PIN_DIO_G1);
SevenSegmentFun       green2(PIN_CLK_Green, PIN_DIO_G2);
SevenSegmentFun     green3(PIN_CLK_Green, PIN_DIO_G3);
SevenSegmentFun      red1(PIN_CLK_Red, PIN_DIO_R1);
SevenSegmentFun       red2(PIN_CLK_Red, PIN_DIO_R2);
SevenSegmentFun     red3(PIN_CLK_Red, PIN_DIO_R3);
SevenSegmentFun           orange1(PIN_CLK_Orange, PIN_DIO_O1); // SegmentExtended pour utiliser la methode "PrintTime"
SevenSegmentFun        orange2(PIN_CLK_Orange, PIN_DIO_O2); //SegmentTM1637 pour utiliser la methode "print" permet d'enlever les ":" entre les chiffres
SevenSegmentFun       orange3(PIN_CLK_Orange, PIN_DIO_O3);



void setup() {


  pinMode(PIN_CLK_Red, OUTPUT);
  pinMode(PIN_DIO_R1, OUTPUT);
  pinMode(PIN_DIO_R2, OUTPUT);
  pinMode(PIN_DIO_R3, OUTPUT);
  pinMode(PIN_CLK_Green, OUTPUT);
  pinMode(PIN_DIO_G1, OUTPUT);
  pinMode(PIN_DIO_G2, OUTPUT);
  pinMode(PIN_DIO_G3, OUTPUT);
  pinMode(PIN_CLK_Orange, OUTPUT);
  pinMode(PIN_DIO_O1, OUTPUT);
  pinMode(PIN_DIO_O2, OUTPUT);
  pinMode(PIN_DIO_O3, OUTPUT);


  red1.begin();
  red2.begin();
  red3.begin();
  red2.setColonOn(0); // Switch off ":" for red "year"

  green1.begin();
  green2.begin();
  green3.begin();

  orange1.begin();
  orange2.begin();
  orange3.begin();
  orange2.setColonOn(0); // Switch off ":" for orange "year"

  red1.setBacklight(backlightR);
  red2.setBacklight(backlightR);
  red3.setBacklight(backlightR);
  green1.setBacklight(backlightG);
  green2.setBacklight(backlightG);
  green3.setBacklight(backlightG);
  orange1.setBacklight(backlightO);
  orange2.setBacklight(backlightO);
  orange3.setBacklight(backlightO);

  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    red1.print(F("Err"));
    red2.print(F("rtc"));
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // sets date and time to the time when the sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.println("Start");
  startPlayback(); // play startup sound
}

void loop() {
  now = rtc.now();

  red1.print(1105, true);
  red2.print(1955, true);
  red3.printTime(now.hour(), now.minute(), true);

  sprintf(data, "%02d%02d", now.month(), now.day());
  green1.print(data);
  green2.print(now.year());
  green3.printTime(now.hour(), now.minute(), true);

  orange1.print(1026, true);
  orange2.print(1985, true);
  orange3.printTime(now.hour(), now.minute(), true);


  if ( now.minute() == 0 && now.second() == 0)
  {
    red1.snake(1);
    red2.snake(1);
    red3.snake(1);

    green1.snake(1);
    green2.snake(1);
    green3.snake(1);

    orange1.snake(1);
    orange2.snake(1);
    orange3.snake(1);

  }

  delay(500);

}

// orange3.printTime(00, now.second(), true);
