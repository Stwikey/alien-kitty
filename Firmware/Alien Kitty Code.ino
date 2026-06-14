// C++ code
//
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// rotary encoder
const int encoderPinA = 9;
const int encoderPinB = 10;
const int buttonPin = 7;

int encoderPos = 0;
int pinALastState;
int pinAState;
int death = 0;

const int rotationlimit = 90;


// Face components 
// Default Face
byte default1x14[] = { B11111, B11111, B11111, B11111, B11111, B11111, B11110, B11110 };
byte default0x1[] = { B01111, B01111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte default0x2[] = { B11110, B11110, B11111, B11111, B11111, B11111, B11111, B11111 };
byte default0x13[] = { B01111, B01111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte default0x14[] = { B11110, B11110, B11111, B11111, B11111, B11111, B11111, B11111 };
byte default1x1[] = { B11111, B11111, B11111, B11111, B11111, B11111, B01111, B01111 };
byte default1x2[] = { B11111, B11111, B11111, B11111, B11111, B11111, B11110, B11110 };
byte default1x13[] = { B11111, B11111, B11111, B11111, B11111, B11111, B01111, B01111 };


void defaultface(){
  lcd.createChar(0, default1x14);
  lcd.createChar(1, default0x1);
  lcd.createChar(2, default0x2);
  lcd.createChar(3, default0x13);
  lcd.createChar(4, default0x14);
  lcd.createChar(5, default1x1);
  lcd.createChar(6, default1x2);
  lcd.createChar(7, default1x13);
  
  lcd.setCursor(14, 1);
  lcd.write(byte(0));
  
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  
  lcd.setCursor(2, 0);
  lcd.write(byte(2));
  
  lcd.setCursor(13, 0);
  lcd.write(byte(3));
  
  lcd.setCursor(14, 0);
  lcd.write(byte(4));
  
  lcd.setCursor(1, 1);
  lcd.write(byte(5));
  
  lcd.setCursor(2, 1);
  lcd.write(byte(6));
  
  lcd.setCursor(13, 1);
  lcd.write(byte(7));
}

// Happy face
byte happy0x1[] = { B00100, B00110, B00111, B00011, B00001, B00000, B00000, B00000 };
byte happy0x2[] = { B00000, B00000, B00000, B10000, B11000, B11100, B01110, B00110 };
byte happy0x14[] = { B00000, B00000, B00001, B00011, B00111, B01110, B11100, B11000 };
byte happy0x15[] = { B01000, B11000, B11000, B10000, B00000, B00000, B00000, B00000 };
byte happy1x1[] = { B00000, B00000, B00000, B00001, B00011, B00111, B00110, B00100 };
byte happy1x2[] = { B00110, B01110, B11100, B11000, B10000, B00000, B00000, B00000 };
byte happy1x14[] = { B11000, B11100, B01110, B00111, B00011, B00001, B00000, B00000 };
byte happy1x15[] = { B00000, B00000, B00000, B00000, B10000, B11000, B11000, B01000 };

void happyface(){
  lcd.createChar(0, happy0x1);
  lcd.createChar(1, happy0x2);
  lcd.createChar(2, happy0x14);
  lcd.createChar(3, happy0x15);
  lcd.createChar(4, happy1x1);
  lcd.createChar(5, happy1x2);
  lcd.createChar(6, happy1x14);
  lcd.createChar(7, happy1x15);
  
  lcd.setCursor(1, 0);
  lcd.write(byte(0));
  lcd.setCursor(2, 0);
  lcd.write(byte(1));
  lcd.setCursor(14, 0);
  lcd.write(byte(2));
  lcd.setCursor(15, 0);
  lcd.write(byte(3));
  lcd.setCursor(1, 1);
  lcd.write(byte(4));
  lcd.setCursor(2, 1);
  lcd.write(byte(5));
  lcd.setCursor(14, 1);
  lcd.write(byte(6));
  lcd.setCursor(15, 1);
  lcd.write(byte(7));
  
}

// Dead face 
byte dead0x11[] = { B00100, B00110, B00111, B00011, B00001, B00000, B00000, B00000 };
byte dead0x1[] = { B00100, B00110, B00111, B00011, B00001, B00000, B00000, B00000 };
byte dead0x2[] = { B00000, B00000, B00000, B10000, B11000, B11100, B01110, B00111 };
byte dead0x3[] = { B00000, B00000, B00000, B00001, B00011, B00111, B01110, B11100 };
byte dead0x4[] = { B00100, B01100, B11100, B11000, B10000, B00000, B00000, B00000 };
byte dead0x12[] = { B00000, B00000, B00000, B10000, B11000, B11100, B01110, B00111 };
byte dead0x13[] = { B00000, B00000, B00000, B00001, B00011, B00111, B01110, B11100 };
byte dead0x14[] = { B00100, B01100, B11100, B11000, B10000, B00000, B00000, B00000 };
byte dead1x1[] = { B00000, B00000, B00000, B00000, B00001, B00011, B00111, B00110 };
byte dead1x2[] = { B00011, B00111, B01110, B11100, B11000, B10000, B00000, B00000 };
byte dead1x3[] = { B11000, B11100, B01110, B00111, B00011, B00001, B00000, B00000 };
byte dead1x4[] = { B00000, B00000, B00000, B00000, B10000, B11000, B11100, B01100 };
byte dead1x11[] = { B00000, B00000, B00000, B00000, B00001, B00011, B00111, B00110 };
byte dead1x12[] = { B00011, B00111, B01110, B11100, B11000, B10000, B00000, B00000 };
byte dead1x13[] = { B11000, B11100, B01110, B00111, B00011, B00001, B00000, B00000 };
byte dead1x14[] = { B00000, B00000, B00000, B00000, B10000, B11000, B11100, B01100 };

void deadface(){
  lcd.createChar(0, dead0x11);
  lcd.setCursor(11, 0);
  lcd.write(byte(0));
  
  lcd.createChar(1, dead0x1);
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  
  lcd.createChar(2, dead0x2);
  lcd.setCursor(2, 0);
  lcd.write(byte(2));
  
  lcd.createChar(3, dead0x3);
  lcd.setCursor(3, 0);
  lcd.write(byte(3));
  
  lcd.createChar(4, dead0x4);
  lcd.setCursor(4, 0);
  lcd.write(byte(4));
  
  lcd.createChar(5, dead0x12);
  lcd.setCursor(12, 0);
  lcd.write(byte(5));
  
  lcd.createChar(6, dead0x13);
  lcd.setCursor(13, 0);
  lcd.write(byte(6));
  
  lcd.createChar(7, dead0x14);
  lcd.setCursor(14, 0);
  lcd.write(byte(7));
  
  lcd.createChar(8, dead1x1);
  lcd.setCursor(1, 1);
  lcd.write(byte(8));
  
  lcd.createChar(9, dead1x2);
  lcd.setCursor(2, 1);
  lcd.write(byte(9));
  
  lcd.createChar(10, dead1x3);
  lcd.setCursor(3, 1);
  lcd.write(byte(10));
  
  lcd.createChar(11, dead1x4);
  lcd.setCursor(4, 1);
  lcd.write(byte(11));
  
  lcd.createChar(12, dead1x11);
  lcd.setCursor(11, 1);
  lcd.write(byte(12));
  
  lcd.createChar(13, dead1x12);
  lcd.setCursor(12, 1);
  lcd.write(byte(13));
  
  lcd.createChar(14, dead1x13);
  lcd.setCursor(13, 1);
  lcd.write(byte(14));
  
  lcd.createChar(15, dead1x14);
  lcd.setCursor(14, 1);
  lcd.write(byte(15));
}

void setup()
{ 
  pinMode(6, OUTPUT);
  analogWrite(6, 150);
  
  pinMode(buttonPin, INPUT);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  lcd.begin(16,2);
 
  defaultface();
  pinALastState = digitalRead(encoderPinA);
}


void loop()
{
  delay(10); // Delay a little bit to improve simulation performance
  pinAState = digitalRead(encoderPinA);
  if (pinAState != pinALastState){
    if (digitalRead(encoderPinB) != pinAState) {
      encoderPos ++;
    }
    else{
      encoderPos --;
    }
  }
  if (abs(encoderPos) >= rotationlimit){
      if (death != 1) { 
        lcd.clear();
        deadface();
        death = 1;
      }
    }
    else {
      if (death != 0) { 
        lcd.clear();
        defaultface();
        death = 0;
      }
    }
  if (digitalRead(buttonPin) == HIGH) {
    lcd.clear();
    analogWrite(9,250);
    happyface();
    delay(1000);
    lcd.clear();
    analogWrite(9,0);
    
    if (abs(encoderPos) >= rotationlimit) {
      deadface();
      death = 1;
    }
    else {
      defaultface();
      death = 0;
    }
  }
  pinALastState = pinAState;
}
