/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arisinfg from the use of this software.
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
#include "vector.hpp"
#include <cmath>
namespace gamelib3 {

// -----------------------------------------------------------------------------
//  constructor (with initialisers)
// -----------------------------------------------------------------------------
Vector3::Vector3(float xi, float yi, float zi) {
  x = xi;
  y = yi;
  z = zi;
}

Vector3::Vector3(int xi, int yi, int zi) {
  x = static_cast<float>(xi);
  y = static_cast<float>(yi);
  z = static_cast<float>(zi);
}

// -----------------------------------------------------------------------------
//  constructor (with initialisers)
// -----------------------------------------------------------------------------
Vector3::Vector3(float xi, float yi) {
  x = xi;
  y = yi;
  z = 0;
}

// -----------------------------------------------------------------------------
// [] operator
// -----------------------------------------------------------------------------
float Vector3::operator[](INDEX idx) const {
  switch (idx) {
    case X:
      return x;
    case Y:
      return y;
    case Z:
      return z;
  }
  return 0;
}

// -----------------------------------------------------------------------------
//   += operator
// -----------------------------------------------------------------------------
Vector3 &Vector3::operator+=(const Vector3 &rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;

  return *this;
}

// -----------------------------------------------------------------------------
//   -= operator
// -----------------------------------------------------------------------------
Vector3 &Vector3::operator-=(const Vector3 &rhs) {
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;

  return *this;
}

// -----------------------------------------------------------------------------
//   *= operator
// -----------------------------------------------------------------------------
Vector3 &Vector3::operator*=(const Vector3 &rhs) {
  x *= rhs.x;
  y *= rhs.y;
  z *= rhs.z;

  return *this;
}

// -----------------------------------------------------------------------------
//   *= operator (sccalar)
// -----------------------------------------------------------------------------
Vector3 &Vector3::operator*=(const float rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;

  return *this;
}

// -----------------------------------------------------------------------------
//   /= operator (scalar)
// -----------------------------------------------------------------------------
Vector3 &Vector3::operator/=(const float rhs) {
  x /= rhs;
  y /= rhs;
  z /= rhs;

  return *this;
}

// -----------------------------------------------------------------------------
//   + operator
// -----------------------------------------------------------------------------
Vector3 const Vector3::operator+(const Vector3 &rhs) const {
  return Vector3(*this) += rhs;
}

// -----------------------------------------------------------------------------
//   - operator
// -----------------------------------------------------------------------------
Vector3 const Vector3::operator-(const Vector3 &rhs) const {
  return Vector3(*this) -= rhs;
}

// -----------------------------------------------------------------------------
//   * operator (scalar)
// -----------------------------------------------------------------------------
Vector3 const Vector3::operator*(const float rhs) const {
  return Vector3(*this) *= rhs;
}

// -----------------------------------------------------------------------------
//   / operator (scalar)
// -----------------------------------------------------------------------------
Vector3 const Vector3::operator/(const float rhs) const {
  return Vector3(*this) /= rhs;
}

// -----------------------------------------------------------------------------
//   cross product operator
// -----------------------------------------------------------------------------
Vector3 const Vector3::operator^(Vector3 &v) {
  return Vector3(y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x);
}

// -----------------------------------------------------------------------------
//   dot product operator
// -----------------------------------------------------------------------------
float Vector3::operator*(Vector3 &rhs) {
  return (x * rhs.x + y * rhs.y + z * rhs.z);
}

// -----------------------------------------------------------------------------
//   scalar + operator
// -----------------------------------------------------------------------------
const Vector3 Vector3::operator+(const float scalar) {
  return Vector3(this->x + scalar, this->y + scalar, this->z + scalar);
}

// -----------------------------------------------------------------------------
//   scalar - operator
// -----------------------------------------------------------------------------
const Vector3 Vector3::operator-(const float scalar) {
  return Vector3(this->x - scalar, this->y - scalar, this->z - scalar);
}

// -----------------------------------------------------------------------------
//  normalise
// -----------------------------------------------------------------------------
Vector3 Vector3::normalise() {
  Vector3 normalized(x, y, z);

  float m = sqrtf(x * x + y * y + z * z);

  if (m <= TOL) {
    m = 1;
  }

  normalized.x /= m;
  normalized.y /= m;
  normalized.z /= m;

  if (fabsf(normalized.x) < TOL) {
    normalized.x = 0;
  }
  if (fabsf(normalized.y) < TOL) {
    normalized.y = 0;
  }
  if (fabsf(normalized.z) < TOL) {
    normalized.z = 0;
  }

  return normalized;
}

// -----------------------------------------------------------------------------
//  reflect
// -----------------------------------------------------------------------------
Vector3 Vector3::reflect(Vector3 &normal) const {
  float dot = (x * normal.x) + (y * normal.y);
  dot *= 2;
  Vector3 reflected = normal * dot - *this;
  return reflected.reverse();
}

// -----------------------------------------------------------------------------
//  project
// -----------------------------------------------------------------------------
float Vector3::projectionOn(Vector3 line) {
  line = line.normalise();
  return dotProduct(line);
}

// -----------------------------------------------------------------------------
//  get perpendicular (normal vector)
// -----------------------------------------------------------------------------
Vector3 Vector3::perpendicular() {
  Vector3 perp(y, -x);
  return perp;
}

// -----------------------------------------------------------------------------
//  rotated
// -----------------------------------------------------------------------------
Vector3 Vector3::rotate(float a, float x_origin, float y_origin) const {
  a = RADIANS(a);

  Vector3 rotated = *this;

  rotated.x -= x_origin;
  rotated.y -= y_origin;

  float nx = cosf(a) * rotated.x - sinf(a) * rotated.y;
  float ny = sinf(a) * rotated.x + cosf(a) * rotated.y;

  rotated.x = nx;
  rotated.y = ny;

  rotated.x += x_origin;
  rotated.y += y_origin;

  return rotated;
}

// -----------------------------------------------------------------------------
// multiply
// -----------------------------------------------------------------------------
Vector3 Vector3::multiply(const Vector3 &rhs) const {
  return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

// -----------------------------------------------------------------------------
//   test for equality
// -----------------------------------------------------------------------------
bool Vector3::equals(const Vector3 &v) {
  if (Floats::equal(x, v.x) && Floats::equal(y, v.y) && Floats::equal(z, v.z)) {
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------
//   test for equality
// -----------------------------------------------------------------------------
bool Vector3::equals(const Vector3 &v, float tolerance) {
  return (Floats::equal(x, v.x, tolerance) &&
          Floats::equal(y, v.y, tolerance) && Floats::equal(z, v.z, tolerance));
}

// -----------------------------------------------------------------------------
//   roundf the angle to nearest x degrees
// -----------------------------------------------------------------------------
Vector3 Vector3::roundAngle(int nearest_angle) {
  // vector to return
  Vector3 rounded;

  // convert to radians
  float nearest_radians = RADIANS(nearest_angle);

  // get the angle of this vector
  float angle = atan2f(y, x);

  // remainder between 2 angles
  float remainder = std::fmod(angle, nearest_radians);

  // if there is a remainder, do the roundfing
  if (remainder > TOL) {
    float new_angle = roundf(angle / nearest_radians) * nearest_radians;

    rounded.x = cosf(new_angle);
    rounded.y = sinf(new_angle);
  } else {
    rounded.x = x;
    rounded.y = y;
    rounded.z = z;
  }

  if (fabsf(rounded.x) < TOL) {
    rounded.x = 0;
  }
  if (fabsf(rounded.y) < TOL) {
    rounded.y = 0;
  }
  if (fabsf(rounded.z) < TOL) {
    rounded.z = 0;
  }

  return rounded.normalise();
}

// -----------------------------------------------------------------------------
//   perpProduct
// -----------------------------------------------------------------------------
float Vector3::perpProduct(const Vector3 &v, bool right_normal) {
  float componentY, componentX;

  if (right_normal) {
    componentX = y * v.x;
    componentY = -1 * x * v.y;
  } else {
    componentX = -1 * y * v.x;
    componentY = x * v.y;
  }
  return componentX + componentY;
}

// -----------------------------------------------------------------------------
//   polar
// -----------------------------------------------------------------------------
Vector3 Vector3::polar(float mag, float radians) {
  return {mag * cosf(radians), mag * sinf(radians)};
}

// -----------------------------------------------------------------------------
//   setMagnitude
// -----------------------------------------------------------------------------
Vector3 Vector3::setMagnitude(float mag) {
  float ang_current = angle();
  return polar(mag, ang_current);
}

// -----------------------------------------------------------------------------
// get magnitude of this vector
// -----------------------------------------------------------------------------
float Vector3::magnitude() const { return sqrtf(x * x + y * y + z * z); }

// -----------------------------------------------------------------------------
// get magnitude of this vector in 2d
// -----------------------------------------------------------------------------
float Vector3::magnitude2d() { return sqrtf(x * x + y * y); }

// -----------------------------------------------------------------------------
// get unit vector
// -----------------------------------------------------------------------------
Vector3 Vector3::unit(Vector3 v) { return v / v.magnitude(); }

// -----------------------------------------------------------------------------
// get mag squared
// -----------------------------------------------------------------------------
float Vector3::magSquared() { return magnitude() * magnitude(); }

// -----------------------------------------------------------------------------
// get reversed
// -----------------------------------------------------------------------------
Vector3 Vector3::reverse() {
  Vector3 reversed(-x, -y, -z);
  return reversed;
}

// -----------------------------------------------------------------------------
//   dot product
// -----------------------------------------------------------------------------
float Vector3::dotProduct(const Vector3 &v) const {
  return (x * v.x + y * v.y + z * v.z);
}

// -----------------------------------------------------------------------------
//   get angle in degrees
// -----------------------------------------------------------------------------
float Vector3::angle() { return DEGREES(atan2f(y, x)); }

// -----------------------------------------------------------------------------
//   reset components to zero
// -----------------------------------------------------------------------------
void Vector3::reset() { x = y = z = 0; }

// -----------------------------------------------------------------------------
//   normalizes all components to 1's or 0's
// -----------------------------------------------------------------------------
Vector3 Vector3::normalizeToUnits() {
  Vector3 ret;
  if (x > 0) {
    ret.x = 1;
  } else if (x < 0) {
    ret.x = -1;
  }

  if (y > 0) {
    ret.y = 1;
  } else if (y < 0) {
    ret.y = -1;
  }
  return ret;
}

// -----------------------------------------------------------------------------
// find if a vector is moving towards a point
// -----------------------------------------------------------------------------
bool Vector3::isMovingTowards(Vector3 testPoint, Vector3 objectPosition,
                              Vector3 objectVelocity) {
  Vector3 toPoint = testPoint - objectPosition;
  float dot = toPoint.dotProduct(objectVelocity);
  return dot > 0;
}

}  // namespace gamelib3
