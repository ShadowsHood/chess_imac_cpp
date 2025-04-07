#include "./utils.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "../lib/miniaudio/miniaudio.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

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
  case Type::Elevator:
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
