#pragma once

#include "../physics/movable.hpp"

#include <SFML/Graphics/View.hpp>

namespace gamelib3 {

class Camera : public Movable {
 public:
  virtual void Step(float dt) override;
  sf::View viewport;

 protected:
  Movable *following;
};

}  // namespace gamelib3
