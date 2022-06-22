#include "HomeSpan.h"

struct My_Lamp : Service::LightBulb {
  int ledPin;
  SpanCharacteristic *power;
  SpanCharacteristic *level;

  My_Lamp(int ledPin) : Service::LightBulb(){
    power=new Characteristic::On();
    level=new Characteristic::Brightness(50);
    level->setRange(5, 100, 1);
    this->ledPin = ledPin;
    pinMode(ledPin, OUTPUT);
  }

  boolean update(){
    LOG1("Updating On/Off LED on pin=");
    LOG1(ledPin);
    LOG1("  New Power=");
    LOG1(power->getNewVal()?"true":"false");
    LOG1("  New level=");
    LOG1(level->getNewVal());
    LOG1("\n");
    digitalWrite(ledPin, power->getNewVal() * level->getNewVal() * 2.55);
    return(true);
  }
};
