// #include "Insta360.h"
#include "Button.h"
#include "Event.h"
// #include "Dispatcher.h"

// Camera cam;

// Observer observer;
// Dispatcher<ButtonClickEvent> dispatcher;
Button recordButton(14, 23); //, dispatcher);

void IRAM_ATTR recordISR() {
  recordButton.click();
}


void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  // cam.setup();
  recordButton.setup();
  attachInterrupt(recordButton.getButtonPin(), recordISR, FALLING);

  // dispatcher.subscribe(ButtonClickEvent::RECORD, 
  //                      std::bind( &Observer::handle, observer, std::placeholders::_1));

}

void loop() {
  // cam.loop();
  recordButton.loop();
}