#ifndef DISPATCHER_H
#define DISPATCHER_H


#include "Event.h"
#include <functional>
#include <map>
#include <vector>
#include <algorithm>


template<typename T>
class Dispatcher{
private:
  using SlotType = std::function<void(const Event<T>&)>;
  std::map<T, std::vector<SlotType>> _observers;
public:

  /**
   * Subscribe an observer
   * @param type  The type of the function to listen to.
   * @param funct function of the observer
   */
  void subscribe(T type, const SlotType& funct){
    Serial.println("Dispatcher::subscribe");
    _observers[type].push_back(funct);
    Serial.println("Dispatcher::subscribed");
  };

  /**
   * Send the event to all the observers
   * @param event event to post
   */
  // void post(Event<T>& event){
  //   Serial.println("Dispatcher::post");
  //   if(_observers.find(event.type()) == _observers.end())
  //     return;

  //   //Loop though all observers. If the event is not handled yet we continue to process it.
  //   for(auto&& observer : _observers.at(event.type())){
  //     if(!event.isHandled()) observer(event);  
  //   }
  // };
private:
};

// class Dispatcher {
// private:
//   std::map<Event::DescriptorType, std::vector<SlotType>> _observers;

// public:
//   using SlotType = std::function<void(const Event&)>;

//   void subscribe(const Event::DescriptorType& descriptor, SlotType&& slot) {
//     _observers[descriptor].push_back(slot);
//   }

//   void post(const Event& event) const {
//     auto type = event.type();

//     if (_observers.find(type) == _observers.end()) {
//       return;
//     }

//     auto&& observers = _observers.at(type);

//     for (auto&& observer : observers) {
//       observer(event);
//     }
//   }
// };

#endif