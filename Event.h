#include <functional>
#include <map>

class Event {
  public:
    virtual ~Event();

    using DescriptorType const char*;

    virtual DescriptorType type() const = 0;
};


class ButtonClickEvent : public Event {
public:
  ButtonClickEvent();
  virual ~ButtonClickEvent();

  static constexpr DescriptorType descriptor = "ButtonClickedEvent";

  virtual DescriptorType type() const {
    return descriptor;
  }
};


class Dispatcher {
private:
  std::map<Event::DescriptorType, std::vector<SlotType>> _observers;

public:
  using SlotType = std::function<void(const Event&)>;

  void subscribe(const Event::DescriptorType& descriptor, SlotType&& slot);

  void post(const Event& event) const;
};


void Dispatcher::subscribe(const Event::DescriptorType& descriptor, SlotType&& slot) {
  _observers[descriptor].push_back(slot);
}

void Dispatcher::post(const Event& event) const {
  auto type = event.type();

  if (_observers.find(type) == _observers.end()) {
    return;
  }

  auto&& observers = _observers.at(type);

  for (auto&& observer : observers) {
    observer(event);
  }
}