#pragma once
#include <DirectXMath.h>

#include <vector>

#include "Math.h"

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

// Default camera values
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.f;
constexpr float SENSITIVITY = 0.2f;
constexpr float ZOOM = 45.0f;

class Camera {
 public:
  Vec3 position_;
  Vec3 front_;
  Vec3 up_;
  Vec3 right_;
  Vec3 world_up_;

  float yaw_;
  float pitch_;

  float speed_;
  float sensitivity_;
  float zoom_;

  Camera(Vec3 position = Vec3(0.0f, 0.0f, 0.0f),
         Vec3 up = Vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  DirectX::XMMATRIX GetViewMatrix();

  void ProcessKeyboard(Direction direction, float deltaTime);

  void ProcessMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true);

  void ProcessMouseScroll(float yoffset);

 private:
  void updateCameraVectors();
};
