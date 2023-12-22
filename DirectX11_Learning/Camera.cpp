#include "Camera.h"
Camera::Camera(Vec3 position, Vec3 up, float yaw, float pitch)
    : front_(Vec3(0.0f, 0.0f, 1.0f)),
      speed_(SPEED),
      sensitivity_(SENSITIVITY),
      zoom_(ZOOM) {
  position_ = position;
  world_up_ = up;
  yaw_ = yaw;
  pitch_ = pitch;
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch)
    : front_(Vec3(0.0f, 0.0f, -1.0f)),
      speed_(SPEED),
      sensitivity_(SENSITIVITY),
      zoom_(ZOOM) {
  position_ = Vec3(posX, posY, posZ);
  world_up_ = Vec3(upX, upY, upZ);
  yaw_ = yaw;
  pitch_ = pitch;
  updateCameraVectors();
}

DirectX::XMMATRIX Camera::GetViewMatrix() {
  DirectX::XMVECTOR pos = {position_.x, position_.y, position_.z};
  DirectX::XMVECTOR front = {position_.x + front_.x, position_.y + front_.y,
                             position_.z + front_.z};
  DirectX::XMVECTOR up = {up_.x, up_.y, up_.z};
  return DirectX::XMMatrixLookAtLH(pos, front, up);
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime) {
  float velocity = speed_ * deltaTime;
  Vec3 front = {front_.x, 0, front_.z};
  if (direction == FORWARD) position_ = position_ + front * velocity;
  if (direction == BACKWARD) position_ = position_ - front * velocity;
  if (direction == RIGHT) position_ = position_ - right_ * velocity;
  if (direction == LEFT) position_ = position_ + right_ * velocity;
  if (direction == UP) position_ = position_ + up_ * velocity;
  if (direction == DOWN) position_ = position_ - up_ * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  bool constrainPitch) {
  xoffset *= sensitivity_;
  yoffset *= sensitivity_;

  yaw_ += xoffset;
  pitch_ += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (pitch_ > 89.0f) pitch_ = 89.0f;
    if (pitch_ < -89.0f) pitch_ = -89.0f;
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
  zoom_ -= (float)yoffset;
  if (zoom_ < 1.0f) zoom_ = 1.0f;
  if (zoom_ > 45.0f) zoom_ = 45.0f;
}

void Camera::updateCameraVectors() {
  // calculate the new Front vector
  Vec3 front;
  front.x = cos(DirectX::XMConvertToRadians(yaw_)) *
            cos(DirectX::XMConvertToRadians(pitch_));
  front.y = sin(DirectX::XMConvertToRadians(pitch_));
  front.z = sin(DirectX::XMConvertToRadians(yaw_)) *
            cos(DirectX::XMConvertToRadians(pitch_));
  front_ = front.Normalize();
  // also re-calculate the Right and Up vector
  right_ = front_.Cross(world_up_).Normalize();
  up_ = right_.Cross(front_).Normalize();
}
