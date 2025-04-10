#pragma once
#include "../utils.hpp"
#include "./Color.hpp"
#include "./Type.hpp"
#include <imgui.h>
#include <utility>
#include <vector>

class Board;

class Piece {
private:
  Color color;
  Type type;
  char character{};
  bool first_move{true};
  std::string sound{};

public:
  Piece(Color color, Type type, std::string sound)
      : color(color), type(type), sound(std::move(sound)),
        character(get_sprite_char(color, type)) {};
  virtual ~Piece() = default;
  Piece(const Piece &other) = default;
  Piece &operator=(const Piece &other) = default;
  Piece(Piece &&other) = default;
  Piece &operator=(Piece &&other) = default;

  Color get_color() const { return this->color; };
  Type get_type() const { return this->type; };
  char get_char() const { return this->character; };
  bool get_first_move() const { return this->first_move; };
  std::string get_soud() const { return this->sound; };

  virtual std::vector<int> get_possible_moves(const Board &board,
                                              int position) = 0;
  void move(Board &board, int old_position, int new_position);
  void handle_en_passant(Board &board, std::pair<int, int> new_pos_2D) const;
  void update_en_passant_availability(Board &board,
                                      std::pair<int, int> new_pos_2D,
                                      int new_position);
  void promotion(Board &board, int position, char new_type);
};