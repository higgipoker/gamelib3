#include "entity.hpp"
namespace gamelib3 {

DummyMovable GameEntity::dummy_movable;
DummyRenderable GameEntity::dummy_renderable;

GameEntity::GameEntity(Movable* m, Renderable* r)
    : physical_aspect(m), graphical_aspect(r) {}

GameEntity::GameEntity(Movable* m)
    : physical_aspect(m), graphical_aspect(&dummy_renderable) {}

GameEntity::GameEntity(Renderable* r)
    : physical_aspect(&dummy_movable), graphical_aspect(r) {}

GameEntity::~GameEntity() {}


}  // namespace gamelib3
