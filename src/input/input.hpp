#pragma once
#include <SFML/Window/Event.hpp>
namespace gamelib3 {

class InputCallback {
 public:
  virtual void HandleEvent(sf::Event event) = 0;

 protected:
};

}  // namespace gamelib3
