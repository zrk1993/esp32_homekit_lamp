#include <Arduino.h>
#include "HomeSpan.h"
#include "My_Lamp.h"

void setup() {
  Serial.begin(9600);
  
  homeSpan.setLogLevel(2);
  homeSpan.begin(Category::Lighting, "HomeSpan LightBulb");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Simple LED"); 
    new My_Lamp(25);
}

void loop() {
  homeSpan.poll();
}