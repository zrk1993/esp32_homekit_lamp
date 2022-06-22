#include "HomeSpan.h"

struct My_Lamp : Service::LightBulb {
  int ledPin;
  SpanCharacteristic *power;
  SpanCharacteristic *level;

  My_Lamp(int ledPin) : Service::LightBulb(){
    power=new Characteristic::On();
    level=new Characteristic::Brightness(50);
    level->setRange(0, 100, 10);
    this->ledPin = ledPin;
    pinMode(ledPin, OUTPUT);
    dacWrite(ledPin, 255);
  }

  boolean update(){
    int val = power->getNewVal() * level->getNewVal() * 2.55;
    Serial.printf("update power: %d, level: %d, val: %d\n",  power->getNewVal(), level->getNewVal(), val);
    dacWrite(ledPin, val);
    return(true);
  }
};
