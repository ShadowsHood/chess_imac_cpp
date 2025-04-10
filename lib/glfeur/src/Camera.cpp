#include "Camera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <GLFW/glfw3.h>

#include <algorithm>

namespace glfeur {

glm::mat4 Camera::get_view_matrix() {
  if (_is_track_ball) {
    _position =
        glm::vec3(_radius * cos(glm::radians(_pitch)) * sin(glm::radians(_yaw)),
                  _radius * sin(glm::radians(_pitch)),
                  _radius * cos(glm::radians(_pitch)) * cos(glm::radians(_yaw))

        );
    return glm::lookAt(_position, _target, _up);
  }
  return glm::lookAt(_position, _position + _front, _up);
}

void Camera::process_mouse_movement(double xpos, double ypos) {
  if (_first_mouse) {
    _last_x = static_cast<float>(xpos);
    _last_y = static_cast<float>(ypos);
    _first_mouse = false;
  }

  auto xoffset = static_cast<float>(xpos - _last_x);
  auto yoffset = static_cast<float>(ypos - _last_y);
  _last_x = static_cast<float>(xpos);
  _last_y = static_cast<float>(ypos);

  _yaw -= xoffset * _sensitivity;
  _pitch += yoffset * _sensitivity;

  _pitch = std::min(_pitch, 80.0f);
  _pitch = std::max(_pitch, 5.0f);
}

void Camera::process_scroll(double yoffset) {
  _radius -= static_cast<float>(yoffset) * 0.3f;
  _radius = std::max(_radius, 1.0f);
  _radius = std::min(_radius, 32.0f);
}

void Camera::process_input(int key, int action) {
  if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
    _position += _sensitivity * _front;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    _position -= _sensitivity * _front;
  }
  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    _position -= glm::normalize(glm::cross(_front, _up)) * _sensitivity;
  }
  if (key == GLFW_KEY_C && action == GLFW_PRESS) {
    _position += glm::normalize(glm::cross(_front, _up)) * _sensitivity;
  }
}

// callbacks
void Camera::free_move_callback(int key, int action) {
  if (!is_track_ball() && !_isLocked)
    process_input(key, action);
}

void Camera::zoom_callback(double yoffset) {
  if (is_track_ball() && !_isLocked)
    process_scroll(yoffset);
}

void Camera::track_ball_move_callback(double xpos, double ypos) {
  if (is_track_ball() && !_isLocked)
    process_mouse_movement(xpos, ypos);
}

void Camera::set_first_mouse() { _first_mouse = true; }

bool Camera::is_first_mouse() const { return _first_mouse; }

void Camera::init_mouse_position(double xpos, double ypos) {
  _last_x = static_cast<float>(xpos);
  _last_y = static_cast<float>(ypos);
  _first_mouse = false;
}

} // namespace glfeur
