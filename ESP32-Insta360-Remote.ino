#include <EventManager.h>

#include "Insta360.h"
#include "Button.h"
#include "Events.h"
#include "Led.h"


EventManager eventManager;
const byte connectedLedPin = 22;
const byte advertisingLedPin = 18;
const byte recordLedPin = 23;
Led recordLed(recordLedPin);
Camera cam(connectedLedPin, advertisingLedPin, recordLed, eventManager);

// EventManager btnEventManager;
Button recordButton(14, eventManager);


void IRAM_ATTR recordISR() {
  eventManager.queueEvent(EventType::RECORD_BUTTON_CLICKED, 0);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  recordButton.setup();
  attachInterrupt(recordButton.getButtonPin(), recordISR, FALLING);

  eventManager.addListener(EventType::RECORD_BUTTON_CLICKED,
                           [](int eventCode, int eventParam) {
                             recordButton.handle(eventCode, eventParam);
                           });

  eventManager.addListener(EventType::RECORD_START,
                           [](int eventCode, int eventParam) {
                             cam.recordButtonHandler(eventCode, eventParam);
                           });
  eventManager.addListener(EventType::RECORD_STOP,
                           [](int eventCode, int eventParam) {
                             cam.recordButtonHandler(eventCode, eventParam);
                           });
  eventManager.addListener(EventType::INVALID_RECORDING_STATE,
                           [](int eventCode, int eventParam) {
                             recordButton.handle(eventCode, eventParam);
                           });
  cam.setup();
}

void loop() {
  eventManager.processEvent();
  cam.loop();
  recordLed.loop();
}