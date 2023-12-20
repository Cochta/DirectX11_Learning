#pragma once
#pragma once

#include <stdint.h>

#include <vector>

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
};
struct Vertex {
  Vec3 position;
  Vec2 uv;
  Vec3 color;
};

class GeometryBuilder {
 public:
  std::vector<Vertex> vertices_;
  std::vector<uint32_t> indices_;

  void PushQuad(float scale = 1, Vec3 pos = {0, 0, 0}, Vec3 color = {0, 0, 1});

  void PushCube(float scale = 1, Vec3 pos = {0, 0, 0}, Vec3 color = {0, 0, 1});
};
