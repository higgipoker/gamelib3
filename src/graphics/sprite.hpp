#pragma once
#include "autotexture.hpp"
#include "renderable.hpp"
namespace gamelib3 {

class Sprite : public Renderable {
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
  void Render(sf::RenderTarget& target) override;

  /**
   * @brief SetPosition
   * @param x
   * @param y
   */
  virtual void SetPosition(int x, int y) override;

  /**
   * @brief SetPosition
   * @param position
   */
  virtual void SetPosition(Vector3 _position) override;

  /**
   * @brief move
   */
  virtual void Move(int x, int y) override;

  /**
   * @brief Perspectivize
   * @param z
   * @param distance_from_camera
   */
  virtual void Perspectivize(float z, float width,
                             float camera_height) override;

  /**
   * @brief SetFrame
   * @param frame
   */
  void SetFrame(const int frame);

  /**
   * @brief operator ()
   * @return
   */
  inline sf::Sprite& operator()() { return sprite; }

 protected:
  sf::Sprite sprite;
  AutoTexture texture;
  std::vector<sf::IntRect> rects;
  int current_frame = 0;
  float sprite_scale_factor = 0;
};

}  // namespace gamelib3
