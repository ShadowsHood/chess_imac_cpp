#pragma once
#include "./pieces/Piece.hpp"
#include <array>
#include <imgui.h>
#include <optional>
#include <stack>
#include <vector>

class Board {
private:
  std::array<Piece *, 64> positions_board{};
  std::stack<Piece *> dead_white_pieces{};
  std::stack<Piece *> dead_black_pieces{};

  Color current_player{};
  std::vector<int> next_possible_moves{};
  std::optional<int> selected_piece_position{};
  bool moving{};

private:
  void init_board();

public:
  Board() { this->init_board(); }
  ~Board() = default;
  // Board(const Board &other);
  // Board &operator=(const Board &other);
  // Board(Board &&other) noexcept;
  // Board &operator=(Board &&other) noexcept;

  void draw_board(ImFont *main_font);
  void draw_tile(int i, Piece *piece, ImFont *main_font, bool &is_a_possible_move);
  void draw_dead_pieces(Color color, ImFont *main_font) const;
  void handle_tile_click(int index, Piece *piece, bool &is_a_possible_move);
  void click_playable_piece(int index);
  void click_reachable_tile(int index);

  const std::array<Piece *, 64> &get_positions_board() const {
    return this->positions_board;
  }
  void deselect_piece();

  void set_piece(Piece *piece, int position);

  void kill_piece(Piece *piece, Color color, int position);

  bool is_in_board(std::pair<int, int> position) const;

  Piece *get_piece(int position) {
    return this->positions_board[position] ? this->positions_board[position]
                                           : nullptr;
  };

  bool is_empty(int position) const {
    return this->positions_board[position] == nullptr;
  };

  bool is_other_color(int position, Color color) const {
    return this->positions_board[position]->get_color() != color;
  };
};