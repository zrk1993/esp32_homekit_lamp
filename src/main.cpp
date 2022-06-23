#include <Arduino.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <HomeSpan.h>
#include "DEV_Lamp.h"

AsyncWebServer server(80);

void setupWeb();

void setup() {
  Serial.begin(9600);
  
  //homeSpan.setControlPin(BUTTON_PIN);
	//homeSpan.setStatusPin(LED_STATUS_PIN);
  //homeSpan.setWifiCredentials("", "");
  //homeSpan.setPairingCode("11223344");
  homeSpan.setHostNameSuffix("esp32");
	homeSpan.setLogLevel(1);
	homeSpan.setPortNum(88);
  homeSpan.setStatusAutoOff(10);
  homeSpan.reserveSocketConnections(3);
  homeSpan.setWifiCallback(setupWeb);
  homeSpan.begin(Category::Lighting, "HomeSpan LightBulb");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Simple LED"); 
    new DEV_Lamp(25);
}

void loop() {
  homeSpan.poll();
}

void setupWeb() {
	Serial.print("Starting Server Hub...\n\n");

  // if(!MDNS.begin("esp32")) {
  //   Serial.println("Error starting mDNS\n\n");
  // } else {
  //   Serial.printf("http://esp32.local\n\n");
  // }

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(200, "text/plain", "hello World");
	});

	server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request) {
		String content = "<html><body>Rebooting!  Will return to configuration page in 10 seconds.<br><br>";
		content += "<meta http-equiv = \"refresh\" content = \"10; url = /\" />";
		request->send(200, "text/html", content);
		ESP.restart();
	});

	AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA
	server.begin();
	Serial.println("HTTP server started");
} // setupWeb