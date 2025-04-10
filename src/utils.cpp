#include "./utils.hpp"
#include "draw.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "../lib/miniaudio/miniaudio.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

glm::vec3 get_pos_3D(int index, float tileSize, float spacing) {
  std::pair<int, int> pos2D = get_pos_2D(index);
  float realSpacing =
      spacing + tileSize; // Adjust the spacing to center the tiles
  float x = pos2D.second * (tileSize + realSpacing);
  float z = pos2D.first * (tileSize + realSpacing);
  return glm::vec3(x, 0.0f, z);
}

template <typename T> bool is_in_vec(std::vector<T> &vec, T value) {
  return std::find(vec.begin(), vec.end(), value) != vec.end();
}

void display_vector_pos(std::vector<int> &possible_moves) {
  if (!possible_moves.empty()) {
    std::cout << "Possible moves: " << '\n';
    for (int pos : possible_moves) {
      std::cout << "(" << get_pos_2D(pos).first << "," << get_pos_2D(pos).second
                << ")" << " ";
    }
    std::cout << '\n';
  } else {
    std::cout << "No possible moves" << '\n';
  }
}

int distance_between_two_tiles(int tile1, int tile2) {
  std::pair<int, int> pos1 = get_pos_2D(tile1);
  std::pair<int, int> pos2 = get_pos_2D(tile2);

  int dx = pos1.first - pos2.first;
  int dy = pos1.second - pos2.second;

  return static_cast<int>(std::sqrt(std::pow(dx, 2) + std::pow(dy, 2)));
}

char get_sprite_char(Color color, Type type) {
  char character{};
  switch (type) {
  case Type::Kamikaze:
  case Type::Well:
  case Type::Pawn:
    character = (color == Color::White) ? 'p' : 'o';
    break;
  case Type::Rook:
    character = (color == Color::White) ? 'r' : 't';
    break;
  case Type::Racist:
  case Type::Knight:
    character = (color == Color::White) ? 'h' : 'j';
    break;
  case Type::Fool:
  case Type::Bishop:
    character = (color == Color::White) ? 'b' : 'n';
    break;
  case Type::Queen:
    character = (color == Color::White) ? 'q' : 'w';
    break;
  case Type::King:
    character = (color == Color::White) ? 'k' : 'l';
    break;
  }
  return character;
}

std::string type_string(Type type) {
  switch (type) {
  case Type::Pawn:
    return "pawn";
  case Type::Queen:
    return "queen";
  case Type::King:
    return "king";
  case Type::Rook:
    return "rook";
  case Type::Knight:
    return "knight";
  case Type::Bishop:
    return "bishop";
  case Type::Well:
    return "well";
  case Type::Racist:
    return "racist";
  case Type::Kamikaze:
    return "kamikaze";
  case Type::Fool:
    return "fool";
  default:
    return "unknown";
  }
}

ImVec4 get_tile_color(int i, std::array<float, 32> &tiles_color_offsets) {
  int x = i % 8;
  int y = i / 8;
  if ((x + y) % 2 == 0)
    return ImVec4{0.8f, 0.8f, 0.8f, 1.f};
  float offset = tiles_color_offsets[i/2]; // Variation de la couleur des cases noires selon notre loi gaussienne
  return ImVec4{0.45f - offset, 0.23f - offset, 0.f, 1.f};
}
ImVec4 get_tile_color(int i) {
  int x = i % 8;
  int y = i / 8;
  return (x + y) % 2 == 0 ? ImVec4{0.8f, 0.8f, 0.8f, 1.f}
                          : ImVec4{0.4f, 0.2f, 0.8f, 1.f};
}

glm::vec3 get_tile_color_vec3(int i) {
  int x = i % 8;
  int y = i / 8;
  return (x + y) % 2 == 0 ? glm::vec3(0.8f, 0.8f, 0.8f)
                          : glm::vec3(0.2f, 0.2f, 0.2f);
}

void play_sound(std::string file_name) {
  file_name = "../../sounds/" + file_name;

  ma_engine engine;
  if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) {
      std::cout << "Failed to init engine.\n";
      return;
  }

  ma_sound sound;
  if (ma_sound_init_from_file(&engine, file_name.c_str(), 0, nullptr, nullptr, &sound) != MA_SUCCESS) {
      std::cout << "Failed to load sound.\n";
      ma_engine_uninit(&engine);
      return;
  }

  if (ma_sound_start(&sound) != MA_SUCCESS) {
      std::cout << "Failed to start.\n";
      ma_sound_uninit(&sound);
      ma_engine_uninit(&engine);
      return;
  }

  while (ma_sound_is_playing(&sound)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  ma_sound_uninit(&sound);
  ma_engine_uninit(&engine);
}

