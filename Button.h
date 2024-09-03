#include "Event.h"

class Button {
  const byte btnPin;
  const byte ledPin;
  const Dispatcher dispatcher;
  unsigned long last_button_time = 0;
  bool pressed = false;

  public:
    Button(byte buttonPin, byte lightPin, Dispatcher &attachToDispatcher) : 
      btnPin(buttonPin), ledPin(lightPin), dispatcher(attachToDispatcher) {};

    void setup() {
      pinMode(btnPin, INPUT_PULLUP);
      pinMode(ledPin, OUTPUT);
    }

    void loop() {
      if (pressed) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }

    void click() {
      unsigned long button_time = 0;
      if (button_time - last_button_time > 250) {
        pressed = true;
        last_button_time = button_time;
        dispatcher.post(ButtonClickEvent());
      }
    }

    byte getButtonPin() const {
      return btnPin;
    }
};


class Observer {
  public:
    void handle(const Event& e) {
      if (e.type() == ButtonClickEvent::descriptor) {
        const ButtonClickEvent& clickEvent = static_cast<const ButtonClickEvent&>( e );
        Serial.println(clickEvent.type());
      }
    }

};