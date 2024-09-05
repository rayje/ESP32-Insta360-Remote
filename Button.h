#include <EventManager.h>
#include "Events.h"


class Button {
  const byte btnPin;
  EventManager &eventManager;

  unsigned long last_button_time = 0;
  bool pressed = false;

  public:
    Button(byte buttonPin, EventManager &attachToEM) : 
      btnPin(buttonPin), eventManager(attachToEM) {};

    void setup() {
      pinMode(btnPin, INPUT_PULLUP);
    }

    void click() {
      unsigned long button_time = millis();
      if (button_time - last_button_time > 250) {
        pressed = !pressed;
        last_button_time = button_time;
        // Serial.println("Button::click-inside");

        if (pressed) {
          eventManager.queueEvent(EventType::RECORD_START, 1);
        } else {
          eventManager.queueEvent(EventType::RECORD_STOP, 0);
        }
      }
    }

    byte getButtonPin() const {
      return btnPin;
    }

    void handle(int eventCode, int eventParam) {
      switch (eventCode) {
        case EventType::RECORD_BUTTON_CLICKED:
          click();
          break;
        case EventType::INVALID_RECORDING_STATE:
          // reset pressed state
          pressed = false;
          break;
      }
    }
};