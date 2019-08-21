/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../math/vector.hpp"
namespace gamelib3 {

/**
 * @brief The Primitives class
 */
class Primitives {
 public:
  /**
   * @brief drawLine
   * @param target
   * @param point1
   * @param point2
   * @param thickness
   */
  static void drawLine(sf::RenderTarget &target, const Vector3 &point1,
                       const Vector3 &point2, int thickness);

  /**
   * @brief arc
   * @param target
   * @param x
   * @param y
   * @param radius
   * @param start
   * @param end
   * @param segments
   * @param thickness
   */
  static void arc(sf::RenderTarget &target, float x, float y, float radius,
                  float start, float end, int segments, int thickness);
};

}  // namespace gamelib3
