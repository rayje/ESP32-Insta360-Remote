#include "Event.h"
// #include "Dispatcher.h"


enum class ButtonClickEvent {
  RECORD,
};

class RecordClickEvent : public Event<ButtonClickEvent>
{
public:
  RecordClickEvent() : Event<ButtonClickEvent>(ButtonClickEvent::RECORD, "RecordEvent"){};
  virtual ~RecordClickEvent() = default;
};


class Button {
  const byte btnPin;
  const byte ledPin;
  // Dispatcher<ButtonClickEvent> &dispatcher;
  // RecordClickEvent recordEvent;
  unsigned long last_button_time = 0;
  bool pressed = false;

  public:
    Button(byte buttonPin, byte lightPin) : //, Dispatcher<ButtonClickEvent> &attachToDispatcher) : 
      btnPin(buttonPin), ledPin(lightPin) {};  //, dispatcher(attachToDispatcher) {};

    void setup() {
      pinMode(btnPin, INPUT_PULLUP);
      pinMode(ledPin, OUTPUT);
    }

    void loop() {
      // if (pressed) {
      //   // Serial.println("PRESSED");
      //   digitalWrite(ledPin, HIGH);
      //   // Serial.println("PRESSED-HIGH");
      // } else {
      //   digitalWrite(ledPin, LOW);
      // }
    }

    void click() {
      unsigned long button_time = millis();
      Serial.println("Button::click-outside");
      if (button_time - last_button_time > 250) {
        pressed = !pressed;
        last_button_time = button_time;
        // dispatcher.post(recordEvent);
        Serial.println("Button::click-inside");
      }
    }

    byte getButtonPin() const {
      return btnPin;
    }
};


class Observer {
  public:
    void handle(const Event<ButtonClickEvent>& e) {
      if (e.type() == ButtonClickEvent::RECORD) {
        Serial.println(e.getName().c_str());
      } else {
        Serial.println("Unknown event:");
        Serial.println(e.getName().c_str());
      }
    }

};