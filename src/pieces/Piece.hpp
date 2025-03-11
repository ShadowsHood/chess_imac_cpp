#pragma once
#include <vector>

class Board;

enum class Color : std::uint8_t { White, Black };
enum class Type : std::uint8_t { Pawn, Rook, Knight, Bishop, Queen, King };

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

class Piece {
protected:
  Color color;
  Type type;
  char character{};
  bool first_move{true};

public:
  Piece(Color color, Type type) : color(color), type(type) {};
  virtual ~Piece() = default;

  Color get_color() const { return this->color; };
  Type get_type() const { return this->type; };
  void set_char(Color color, Type type);
  char get_char() const { return this->character; };
  bool get_first_move() const { return this->first_move; };

  virtual std::vector<int> get_possible_moves(const Board &board,
                                              int position) = 0;
  void move(Board &board, int old_position, int new_position);
  void transform_pawn(Board & board, int new_position);
};