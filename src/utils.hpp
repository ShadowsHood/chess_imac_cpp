#pragma once
#include "./elements/Color.hpp"
#include "./elements/Type.hpp"

#include <glm/glm.hpp>
#include <imgui.h>
#include <vector>
#include <string>

glm::vec3 get_pos_3D(int index, float tile_size, float spacing);

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

std::string type_string(Type type);

ImVec4 get_tile_color(int i, std::array<float, 32> const&tiles_color_offsets);
glm::vec3 get_tile_color_vec3(int i, std::array<float, 32> const &tiles_color_offsets);

void play_sound(std::string file_name);

void update_chess_game_title(std::string& window_title);

void funny_message_event(double alpha, double x_m);