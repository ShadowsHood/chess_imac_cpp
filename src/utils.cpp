#include "./utils.hpp"
#include <iostream>

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
  std::pair<int,int> pos1 = get_pos_2D(tile1);
  std::pair<int,int> pos2 = get_pos_2D(tile2);

  int dx = pos1.first - pos2.first;
  int dy = pos1.second - pos2.second;

  return static_cast<int>(std::sqrt(std::pow(dx, 2) + std::pow(dy, 2)));
}