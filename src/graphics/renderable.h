#pragma once

#include "../math/vector.hpp"
#include "autotexture.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace gamelib3 {
struct Renderable {
  // tmp test
  std::string n = "test";
  void draw(sf::RenderTarget& target) { target.draw(sprite); };
  sf::Sprite sprite;
  AutoTexture texture;
  int zorder = 0;
  int id = -1;
};

// -----------------------------------------------------------------------------
// qquality operator
// -----------------------------------------------------------------------------
inline bool operator==(const Renderable& lhs, const int id) {
  return (lhs.id == id);
}

// -----------------------------------------------------------------------------
// sort graphics depending on z order
// -----------------------------------------------------------------------------
//struct {
//  bool operator()(const Renderable &r1, const Renderable &r2) const {
//    return r1.zorder < r2.zorder;
//  }
//} sort_renderable;

inline bool sort_renderable(const Renderable& r1, const Renderable& r2) {
  return r1.zorder < r2.zorder;
}
}  // namespace gamelib3
