#pragma once
#include "./elements/Color.hpp"
#include "./elements/Type.hpp"
#include <vector>
#include <string>

inline std::pair<int, int> get_pos_2D(int pos1D) {
  return std::make_pair(pos1D / 8, pos1D % 8);
}
inline int get_pos_1D(std::pair<int, int> pos2D) {
  return pos2D.first * 8 + pos2D.second;
}
template <typename T> bool is_in_vec(std::vector<T> &vec, T value);

void display_vector_pos(std::vector<int> &possible_moves);

int distance_between_two_tiles(int tile1, int tile2);

char get_sprite_char(Color color, Type type);

void play_sound(std::string file_name);