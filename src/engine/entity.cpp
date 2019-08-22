#include "entity.hpp"
namespace gamelib3 {

DummyMovable GameEntity::dummy_movable;
DummyRenderable GameEntity::dummy_renderable;

GameEntity::GameEntity(Movable* m, Renderable* r)
    : physical_aspect(m), graphical_aspect(r) {
  physical_aspect->renderable = r;
  graphical_aspect->physical = m;
}

GameEntity::GameEntity(Movable* m)
    : physical_aspect(m), graphical_aspect(&dummy_renderable) {
  physical_aspect->renderable = &dummy_renderable;
}

GameEntity::GameEntity(Renderable* r)
    : physical_aspect(&dummy_movable), graphical_aspect(r) {
  graphical_aspect->physical = &dummy_movable;
}

GameEntity::~GameEntity() {}

}  // namespace gamelib3
