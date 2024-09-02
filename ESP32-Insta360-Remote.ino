#include "Button.h"
#include "Insta360.h"
#include "Observer.h"


Camera cam;
Button recordButton(14, 23);

Observer observer;

void IRAM_ATTR recordISR() {
  recordButton.click();
}


void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  cam.setup();
  recordButton.setup();
  attachInterrupt(recordButton.getButtonPin(), recordISR, FALLING);
}

void loop() {
  // cam.loop();
  recordButton.loop();
}