#include <EventManager.h>
#include "Events.h"


class Button {
  protected:
    const byte btnPin;
    EventManager &eventManager;

    unsigned long last_button_time = 0;
    bool pressed = false;

  public:
    Button(byte buttonPin, EventManager &attachToEM) : 
      btnPin(buttonPin), eventManager(attachToEM) {};

    virtual void click() = 0;
    virtual void handle(int eventCode, int eventParam) = 0;

    void setup() {
      pinMode(btnPin, INPUT_PULLUP);
    }

    byte getButtonPin() const {
      return btnPin;
    }

    
};

class RecordButton : public Button {

  public:
    RecordButton(byte buttonPin, EventManager &attachToEM) :
      Button(buttonPin, attachToEM) {};

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

    void handle(int eventCode, int eventParam) {
      switch (eventCode) {
        case EventType::RECORD_BUTTON_CLICKED:
          click();
          break;
        case EventType::DEVICE_NOT_CONNECTED:
          // reset pressed state
          pressed = false;
          break;
      }
    }

};

class PowerButton : public Button {

  public:
    PowerButton(byte buttonPin, EventManager &attachToEM) :
      Button(buttonPin, attachToEM) {};

    void click() {
      unsigned long button_time = millis();
      if (button_time - last_button_time > 250) {
        last_button_time = button_time;

        eventManager.queueEvent(EventType::POWER_OFF, 1);
      }
    }

    void handle(int eventCode, int eventParam) {
      switch (eventCode) {
        case EventType::POWER_BUTTON_CLICKED:
          click();
          break;
        default:
          Serial.print("Unknown event: ");
          Serial.println(eventCode);
      }
    }

};