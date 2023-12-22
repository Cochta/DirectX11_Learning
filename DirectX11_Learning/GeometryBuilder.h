#pragma once
#pragma once

#include <stdint.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <random>
#include <vector>

#include "Math.h"
struct Vertex {
  Vec3 position;
  Vec2 uv;
  Vec3 color;
};

static void Shuffle(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(begin, end, g);
}

class PerlinNoise {
 public:
  PerlinNoise();
  PerlinNoise(unsigned int seed);

  double noise(int x, int z);

 private:
  int* p;
  double fade(double t);
  double lerp(double t, double a, double b);
  double grad(int hash, double x, double z);
};

class GeometryBuilder {
 public:
  std::vector<Vertex> vertices_;
  std::vector<uint32_t> indices_;

  void PushQuad(float scale = 1, Vec3 pos = {0, 0, 0}, Vec3 color = {0, 0, 1});

  void PushCube(float scale = 1, Vec3 pos = {0, 0, 0}, Vec3 color = {0, 0, 1});
};
