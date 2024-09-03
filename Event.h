#ifndef EVENT_H
#define EVENT_H

// #include <functional>
// #include <map>
#include <string>

// class Event {
// public:
//   virtual ~Event();

//   using DescriptorType = const char*;

//   virtual DescriptorType type() const = 0;
// };

// class ButtonClickEvent : public Event {
// public:
//   ButtonClickEvent() = default;
//   virtual ~ButtonClickEvent();

//   static constexpr DescriptorType descriptor = "ButtonClickedEvent";

//   virtual DescriptorType type() const {
//     return descriptor;
//   }
// };

template <typename T>
class Event{
protected:
  T _type;
  std::string _name;
  bool _handled = false;
public:
  Event() = default;
  Event(T type, const std::string& name = "") : _type(type), _name(name){};
  inline const T type() const { return _type;};
  inline const std::string& getName() const { return _name;};
  virtual bool isHandled(){ return _handled;};
private:
};

#endif