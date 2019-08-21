#pragma once
#include "renderable.h"
#include "autotexture.hpp"
namespace gamelib3 {

class Sprite : public Renderable{
 public:
    Sprite() = default;
    /**
   * @brief Sprite
   * @param spritesheet
   * @param rows
   * @param cols
   */
  Sprite(const std::string& spritesheet, int rows, int cols);

  /**
   * @brief Init
   * @param spritesheet
   * @param rows
   * @param cols
   */
  void Init(const std::string& spritesheet, int rows, int cols);

  /**
   * @brief Render
   * @param target
   */
  void Render(sf::RenderTarget &target) override;

protected:
  AutoTexture tex;
};

}  // namespace gamelib3
