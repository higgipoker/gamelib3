#include "entity.hpp"
namespace gamelib3 {
GameEntity::GameEntity(Movable* m, Renderable* r)
    : physical_aspect(m), graphical_aspect(r) {}

GameEntity::~GameEntity() {}
}  // namespace gamelib3
