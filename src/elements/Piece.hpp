#pragma once
#include "../utils.hpp"
#include "./Color.hpp"
#include "./Type.hpp"
#include <vector>

class Board;

class Piece {
private:
  Color color;
  Type type;
  char character{};
  bool first_move{true};

public:
  Piece(Color color, Type type)
      : color(color), type(type), character(get_sprite_char(color, type)) {};
  virtual ~Piece() = default;
  Piece(const Piece &other) = default;
  Piece &operator=(const Piece &other) = default;
  Piece(Piece &&other) = default;
  Piece &operator=(Piece &&other) = default;

  Color get_color() const { return this->color; };
  Type get_type() const { return this->type; };
  char get_char() const { return this->character; };
  bool get_first_move() const { return this->first_move; };

  virtual std::vector<int> get_possible_moves(const Board &board,
                                              int position) = 0;
  void move(Board &board, int old_position, int new_position);
  void handleEnPassant(Board &board, std::pair<int, int> new_pos_2D);
  void updateEnPassantAvailability(Board &board, std::pair<int, int> new_pos_2D,
                                   int new_position);
  void promotion(Board &board, int position);
};