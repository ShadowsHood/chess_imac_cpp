#pragma once
#include <cstdint>

enum class Direction : std::uint8_t {
  Up,
  Down,
  Left,
  Right,
  UpLeft,
  UpRight,
  DownLeft,
  DownRight
};