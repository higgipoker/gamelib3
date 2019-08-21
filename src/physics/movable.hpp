#pragma once
#include "../math/vector.hpp"
namespace gamelib3 {
struct Movable {
  Vector3 position, velocity, force, friction;
  float mass = 1;
  int id;
};

inline bool operator==(const Movable& lhs, const int id) {
  return (lhs.id == id);
}
}  // namespace gamelib3
