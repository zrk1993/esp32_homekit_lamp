struct My_Lamp : Service::LightBulb {
  int ledPin;
  SpanCharacteristic *power;

  My_Lamp(int ledPin) : Service::LightBulb(){
    power=new Characteristic::On();
    this->ledPin = ledPin;
    pinMode(ledPin, OUTPUT);
  }

  boolean update(){
    digitalWrite(ledPin,power->getNewVal());      
    return(true);
  }
};
