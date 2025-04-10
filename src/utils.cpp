#include "./utils.hpp"
#include <iostream>

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