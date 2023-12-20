#include "GeometryBuilder.h"

void GeometryBuilder::PushQuad(float scale, Vec3 pos, Vec3 color) {
  uint32_t offset = vertices_.size();

  vertices_.push_back(
      {(Vec3(-0.5f, -0.5f, 0) + pos) * scale, Vec2(0.0f, 0.0f), color});
  vertices_.push_back(
      {(Vec3(+0.5f, -0.5f, 0) + pos) * scale, Vec2(0.0f, 1.0f), color});
  vertices_.push_back(
      {(Vec3(-0.5f, +0.5f, 0) + pos) * scale, Vec2(1.0f, 0.0f), color});
  vertices_.push_back(
      {(Vec3(+0.5f, +0.5f, 0) + pos) * scale, Vec2(1.0f, 1.0f), color});

  indices_.push_back(0 + offset);
  indices_.push_back(1 + offset);
  indices_.push_back(2 + offset);
  indices_.push_back(1 + offset);
  indices_.push_back(2 + offset);
  indices_.push_back(3 + offset);
}

void GeometryBuilder::PushCube(float scale, Vec3 pos, Vec3 color) {
  uint32_t offset = vertices_.size();

  const Vec3 vertices[] = {
      // Front face
      Vec3(-0.5f, -0.5f, 0.5f),  // 0
      Vec3(+0.5f, -0.5f, 0.5f),  // 1
      Vec3(-0.5f, +0.5f, 0.5f),  // 2
      Vec3(+0.5f, +0.5f, 0.5f),  // 3

      // Back face
      Vec3(-0.5f, -0.5f, -0.5f),  // 4
      Vec3(+0.5f, -0.5f, -0.5f),  // 5
      Vec3(-0.5f, +0.5f, -0.5f),  // 6
      Vec3(+0.5f, +0.5f, -0.5f)   // 7
  };

  const uint32_t cubeIndices[] = {// Front face
                                  0, 1, 2, 1, 3, 2,

                                  // Back face
                                  5, 4, 6, 5, 6, 7,

                                  // Left face
                                  4, 0, 6, 0, 2, 6,

                                  // Right face
                                  1, 5, 3, 5, 7, 3,

                                  // Top face
                                  2, 3, 6, 3, 7, 6,

                                  // Bottom face
                                  1, 0, 5, 0, 4, 5};

  for (int i = 0; i < 8; i ++) {
    vertices_.push_back({(vertices[i] + pos) * scale, Vec2(), color});
  }

  for (int i = 0; i < 36; ++i) {
    indices_.push_back(cubeIndices[i] + offset);
  }
}
