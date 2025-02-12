#pragma once
#include <iostream>
#include <vector>
// #include "Board.hpp"

class Board;

enum class Color { White, Black };
enum class Type { Pawn, Rook, Knight, Bishop, Queen, King };

enum class Direction {
  Up,
  Down,
  Left,
  Right,
  UpLeft,
  UpRight,
  DownLeft,
  DownRight
};

class Piece {
protected:
  Color color;
  Type type;
  char character{};
  bool first_move{true};

public:
  // Piece(): color(Color::White), type(Type::Pawn), position(0) {};
  Piece(Color color, Type type)
      : color(color), type(type) {};
  virtual ~Piece() = default;

  Color get_color() const { return this->color; };
  Type get_type() const { return this->type; };
  void set_char(Color color, Type type);
  char get_char() const { return this->character; };
  bool get_first_move() const { return this->first_move; };

  virtual std::vector<int>
  get_possible_moves(const Board & board, int position) = 0;
  void move(Board & board, int new_position);
};