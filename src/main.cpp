#include <Arduino.h>
#include "HomeSpan.h"
#include "My_Lamp.h"

void setup() {
  Serial.begin(9600);

  homeSpan.begin(Category::Lighting, "HomeSpan LightBulb");
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();

    new Service::LightBulb();
      new Characteristic::On();
}

void loop() {
  homeSpan.poll();
}