#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Uncomment the line below to set the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  // Uncomment the line below to set a specific date & time
  //rtc.adjust(DateTime(YYYY, MM, DD, HH, MM, SS));

  Serial.println("Enter the date (YYYY/MM/DD):");
  while (!Serial.available());
  int year = Serial.parseInt();
  while (!Serial.available());
  int month = Serial.parseInt();
  while (!Serial.available());
  int day = Serial.parseInt();

  Serial.println("Enter the time (HH:MM:SS):");
  while (!Serial.available());
  int hour = Serial.parseInt();
  while (!Serial.available());
  int minute = Serial.parseInt();
  while (!Serial.available());
  int second = Serial.parseInt();

  rtc.adjust(DateTime(year, month, day, hour, minute, second));

  Serial.println("Date & Time set successfully!");
}

void loop() {
  // Code here if needed
}
