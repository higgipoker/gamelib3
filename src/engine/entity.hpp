#pragma once

#include "../graphics/renderable.h"
#include "../physics/movable.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <set>

namespace gamelib3 {

class GameEntity {
 public:
  /**
   * @brief GameEntity
   * @param m
   * @param r
   */
  GameEntity(Movable* m, Renderable* r);

  /**
   * @brief ~GameEntity
   */
  virtual ~GameEntity();

  Movable* physical_aspect = nullptr;
  Renderable* graphical_aspect = nullptr;

 private:
};

// -----------------------------------------------------------------------------
// sort_entities
// -----------------------------------------------------------------------------
inline bool sort_entities(const GameEntity* r1, const GameEntity* r2) {
  if (r1->graphical_aspect && r2->graphical_aspect) {
    return r1->graphical_aspect->zorder < r2->graphical_aspect->zorder;
  }
  return false;
}
}  // namespace gamelib3
