#include <HomeSpan.h>

const int pin1 = 27;
const int pin2 = 26;
const int pin3 = 25;
const int pin4 = 33;

struct DEV_Lamp : Service::LightBulb {
  SpanCharacteristic *power;
  SpanCharacteristic *level;

  DEV_Lamp() : Service::LightBulb(){
    power=new Characteristic::On();
    level=new Characteristic::Brightness(50);
    level->setRange(0, 100, 25);
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }

  boolean update(){
    const int p = power->getNewVal();
    const int l = level->getNewVal();
    Serial.printf("update power: %d, level: %d\n",  p, l);
    if (!p) {
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      Serial.printf("0");
    } else if (l <= 25) {
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      Serial.printf("1");
    } else if (l <= 50) {
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      Serial.printf("2");
    } else if (l <= 75) {
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      Serial.printf("3");
    } else {
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);
      Serial.printf("4");
    }
    return(true);
  }
};
