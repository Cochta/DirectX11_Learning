#pragma once
#include <cmath>
struct Vec2 {
  float x, y;

  Vec2 operator+(const Vec2& other) const { return {x + other.x, y + other.y}; }

  Vec2 operator-(const Vec2& other) const { return {x - other.x, y - other.y}; }
};
struct Vec3 {
  float x, y, z;

  Vec3 operator+(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vec3 operator-(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  Vec3 operator*(const float& scalar) const {
    return {x * scalar, y * scalar, z * scalar};
  }
  float Magnitude() const { return std::sqrt(x * x + y * y + z * z); }

  Vec3 Normalize() const {
    float mag = Magnitude();
    if (mag != 0.0f) {
      return {x / mag, y / mag, z / mag};
    } else {
      return {0.0f, 0.0f, 0.0f};
    }
  }

  Vec3 Cross(const Vec3& other) const {
    return {y * other.z - z * other.y, z * other.x - x * other.z,
            x * other.y - y * other.x};
  }
};
