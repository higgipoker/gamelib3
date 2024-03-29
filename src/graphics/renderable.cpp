#include "renderable.hpp"
#include "primitives.hpp"
namespace gamelib3 {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Renderable::AddPrimitive(sf::Shape* primitive) {
  primitives.emplace_back(primitive);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Renderable::render_primitives(sf::RenderTarget& target) {
  for (auto& primitive : primitives) {
    target.draw(*primitive);
  }

  primitives.clear();
  render_bounds(target);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Renderable::anchor() {
  switch (origin) {
    case AnchorType::None:
      break;
    case AnchorType::TopLeft:
      Move(-bounds.width / 2, -bounds.height / 2);
      break;
    case AnchorType::TopRight:
      Move(bounds.width / 2, -bounds.height / 2);
      break;
    case AnchorType::BottomRight:
      Move(bounds.width / 2, bounds.height / 2);
      break;
    case AnchorType::BottomLeft:
      Move(-bounds.width / 2, bounds.height / 2);
      break;
    case AnchorType::TopCenter:
      Move(0, -bounds.height / 2);
      break;
    case AnchorType::BottomCenter:
      Move(0, bounds.height / 2);
      break;
    case AnchorType::Center:
      break;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Renderable::render_bounds(sf::RenderTarget& target) {
  Primitives::Rect(target, bounds.left, bounds.top, bounds.width,
                   bounds.height);
}
}  // namespace gamelib3
