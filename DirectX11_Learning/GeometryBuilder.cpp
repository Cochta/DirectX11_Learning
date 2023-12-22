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

  const std::vector<Vec3> vertices = {
      Vec3(0.5f, 0.5f, 0.5f),    Vec3(0.5f, -0.5f,
                                      0.5f),  // front
      Vec3(-0.5f, -0.5f, 0.5f),  Vec3(-0.5f, 0.5f, 0.5f),

      Vec3(0.5f, 0.5f, -0.5f),   Vec3(0.5f, 0.5f,
                                      0.5f),  // up
      Vec3(-0.5f, 0.5f, 0.5f),   Vec3(-0.5f, 0.5f, -0.5f),

      Vec3(0.5f, 0.5f, -0.5f),   Vec3(0.5f, -0.5f,
                                      -0.5f),  // back
      Vec3(-0.5f, -0.5f, -0.5f), Vec3(-0.5f, 0.5f, -0.5f),

      Vec3(0.5f, -0.5f, -0.5f),  Vec3(0.5f, -0.5f,
                                      0.5f),  // down
      Vec3(-0.5f, -0.5f, 0.5f),  Vec3(-0.5f, -0.5f, -0.5f),

      Vec3(0.5f, 0.5f, -0.5f),   Vec3(0.5f, -0.5f,
                                      -0.5f),  // right
      Vec3(0.5f, -0.5f, 0.5f),   Vec3(0.5f, 0.5f, 0.5f),

      Vec3(-0.5f, 0.5f, 0.5f),   Vec3(-0.5f, -0.5f,
                                      0.5f),  // left
      Vec3(-0.5f, -0.5f, -0.5f), Vec3(-0.5f, 0.5f, -0.5f)};

  const std::vector<uint32_t> indices = {
      0,  1,  3,  1,  2,  3,  4,  5,  7,  5,  6,  7,  8,  9,  11, 9,  10, 11,
      12, 13, 15, 13, 14, 15, 16, 17, 19, 17, 18, 19, 20, 21, 23, 21, 22, 23,
  };

  for (int i = 0; i < vertices.size(); i++) {
    vertices_.push_back({(vertices[i] + pos) * scale, Vec2(),
                         i >= 4 && i < 8 ? color : Vec3(0.34, 0.22, 0.24)});
  }

  for (int i = 0; i < indices.size(); ++i) {
    indices_.push_back(indices[i] + offset);
  }
}
PerlinNoise::PerlinNoise() {
  // Initialize permutation table (can be shuffled with a seed)
  p = new int[512];
  for (int i = 0; i < 256; i++) {
    p[i] = i;
    p[256 + i] = p[i];
  }
}

PerlinNoise::PerlinNoise(unsigned int seed) {
  // Initialize permutation table using the seed
  // Similar to the previous constructor, but with the seed-based shuffling
  // Implementation omitted for brevity
}

double PerlinNoise::fade(double t) {
  return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) {
  return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double z) {
  int h = hash & 15;
  double u = h < 8 ? x : z, v = h < 4 ? z : h == 12 || h == 14 ? x : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double PerlinNoise::noise(int x, int z) {
  int X = (int)floor(x) & 255, Z = (int)floor(z) & 255;

  x -= floor(x);
  z -= floor(z);

  double u = fade(x), v = fade(z);

  int A = p[X] + Z, AA = p[A], AB = p[A + 1], B = p[X + 1] + Z, BA = p[B],
      BB = p[B + 1];

  return lerp(v, lerp(u, grad(p[AA], x, z), grad(p[BA], x - 1, z)),
              lerp(u, grad(p[AB], x, z - 1), grad(p[BB], x - 1, z - 1)));
}