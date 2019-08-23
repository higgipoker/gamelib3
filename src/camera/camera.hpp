#pragma once

#include "../physics/movable.hpp"

#include <SFML/Graphics/View.hpp>

namespace gamelib3 {

class Camera : public Movable {
 public:
  /**
   * @brief Step
   * @param dt
   */
  virtual void Step(float dt) override;

  /**
   * @brief PopulateAnimations
   */
  virtual void PopulateAnimations() override{};

  sf::View viewport;

 protected:
  Movable *following;
};

}  // namespace gamelib3
