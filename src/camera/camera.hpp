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
  void Step(float dt) override;

  /**
   * @brief PopulateAnimations
   */
  void PopulateAnimations() override{};

  sf::View viewport;

 protected:
  Movable *following = nullptr;
};

}  // namespace gamelib3
