class Button {
  const byte btnPin;
  const byte ledPin;
  unsigned long last_button_time = 0;
  bool pressed = false;

  public:
    Button(byte buttonPin, byte lightPin) : btnPin(buttonPin), ledPin(lightPin) {};

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
      }
    }

    byte getButtonPin() const {
      return btnPin;
    }
};