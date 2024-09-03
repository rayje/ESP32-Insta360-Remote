#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <map>

class Event {
public:
  virtual ~Event();

  using DescriptorType = const char*;

  virtual DescriptorType type() const = 0;
};

class ButtonClickEvent : public Event {
public:
  ButtonClickEvent();
  virtual ~ButtonClickEvent();

  static constexpr DescriptorType descriptor = "ButtonClickedEvent";

  virtual DescriptorType type() const {
    return descriptor;
  }
};


class Dispatcher {
public:
  using SlotType = std::function<void(const Event&)>;

  void subscribe(const Event::DescriptorType& descriptor, SlotType&& slot);

  void post(const Event& event) const;

private:
  std::map<Event::DescriptorType, std::vector<SlotType>> _observers;
};

#endif