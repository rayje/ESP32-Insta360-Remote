#include "Event.h"


class Observer {
  public:
    void handle(const Event& e) {
      if (e.type() == ButtonClickEvent::descriptor) {
        const ButonClickEvent& clickEvent = static_cast<const ButonClickEvent&>( e );
        Serial.println(clickEvent.type());
      }
    }

};