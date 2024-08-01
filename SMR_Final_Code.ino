#include <Wire.h>
#include <EEPROM.h>
#include <RTClib.h> //by Adafruit
#include <LiquidCrystal_I2C.h> //by Frank de Brabander

LiquidCrystal_I2C lcd(0x27, 16, 2); // Address 0x27, 16 columns, 2 rows
RTC_DS1307 RTC;
int temp, inc, hours1, minut, add = 11;
int next = A0;
int INC = A1;
int set_mad = A2;
int HOUR, MINUT, SECOND;
#define buzzer A6

void setup() {
  Wire.begin();
  RTC.begin();
  lcd.backlight();
  lcd.begin(16, 2);
  pinMode(INC, INPUT_PULLUP); // Using internal pull-up resistors
  pinMode(next, INPUT_PULLUP); // Using internal pull-up resistors
  pinMode(set_mad, INPUT_PULLUP); // Using internal pull-up resistors
  pinMode(A6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Medicine reminder");
  lcd.setCursor(0, 1);
  lcd.print(" Using Arduino  ");
  delay(2000);
  if (!RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  int temp = 0, val = 1, temp4;
  DateTime now = RTC.now();
  if (digitalRead(set_mad) == LOW)  // Button pressed logic changed
  {
    lcd.setCursor(0, 0);
    lcd.print("  Set Medicine  ");
    lcd.setCursor(0, 1);
    lcd.print("  Reminder time ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 1");
    defualt();
    time(1);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 2");
    defualt();
    delay(1000);
    time(2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 3");
    defualt();
    time(3);
    lcd.setCursor(0, 0);
    lcd.print("Medicin reminder");
    lcd.setCursor(0, 1);
    lcd.print("  time has set  ");
    delay(2000);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(HOUR = now.hour(), DEC);
  lcd.print(":");
  lcd.print(MINUT = now.minute(), DEC);
  lcd.print(":");
  lcd.print(SECOND = now.second(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  match();
  delay(200);
}

void defualt() {
  lcd.setCursor(0, 1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

void time(int x) {
  int temp = 1;
  while (temp == 1) {
    if (digitalRead(INC) == LOW) {
      HOUR++;
      if (HOUR == 24) {
        HOUR = 0;
      }
      while (digitalRead(INC) == LOW);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == LOW) {
      hours1 = HOUR;
      EEPROM.write(add++, hours1);
      temp = 2;
      while (digitalRead(next) == LOW);
    }
  }
  
  temp = 2; // Resetting temp for the next loop
  while (temp == 2) {
    if (digitalRead(INC) == LOW) {
      MINUT++;
      if (MINUT == 60) { MINUT = 0; }
      while (digitalRead(INC) == LOW);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == LOW) {
      minut = MINUT;
      EEPROM.write(add++, minut);
      temp = 0;
      while (digitalRead(next) == LOW);
    }
  }
  delay(1000);
}

void match() {
  int tem[17];
  for (int i = 11; i < 17; i++) {
    tem[i] = EEPROM.read(i);
  }
  if (HOUR == tem[11] && MINUT == tem[12]) {
   
    lcd.setCursor(0, 0);
    lcd.print("  Take Group One  ");
    lcd.setCursor(0, 1);
    lcd.print("     Medicine     ");
    digitalWrite(10, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(10, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);
    digitalWrite(A6,HIGH);    //Buzzer high
    delay(500);
    digitalWrite(A6,LOW);  //Buzzer low
    delay(500);
    
  }

  if (HOUR == tem[13] && MINUT == tem[14]) {
   
    lcd.setCursor(0, 0);
    lcd.print("  Take Group Two  ");
    lcd.setCursor(0, 1);
    lcd.print("     Medicine     ");
    digitalWrite(11, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(11, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);
     digitalWrite(A6,HIGH);  //Buzzer high
    delay(500);
    digitalWrite(A6,LOW);  //Buzzer low
    delay(500);
    
  }

  if (HOUR == tem[15] && MINUT == tem[16]) {
   
    lcd.setCursor(0, 0);
    lcd.print("Take Group Three ");
    lcd.setCursor(0, 1);
    lcd.print("     Medicine    ");
    digitalWrite(12, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(12, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);
    digitalWrite(A6,HIGH);  //Buzzer high
    delay(500);
    digitalWrite(A6,LOW);  //Buzzer low
    delay(500);
    
  }
}
