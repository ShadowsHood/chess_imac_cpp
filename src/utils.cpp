#include "./utils.hpp"

template <typename T>
bool is_in_vec(std::vector<T> &vec, T value) {
  return std::find(vec.begin(), vec.end(), value) != vec.end();
}

void display_vector_pos(std::vector<int> &possible_moves) {
  if (!possible_moves.empty()) {
    std::cout << "Possible moves: " << std::endl;
    for (int pos : possible_moves) {
      std::cout << "(" << get_pos_2D(pos).first << "," << get_pos_2D(pos).second
                << ")" << " ";
    }
    std::cout << std::endl;
  } else {
    std::cout << "No possible moves" << std::endl;
  }
}