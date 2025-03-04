#pragma once
#include "./pieces/Piece.hpp"
#include <array>
#include <imgui.h>
#include <iostream>
#include <optional>
#include <stack>
#include <vector>

class Board {

private:
  std::array<Piece *, 64> positions_board{};
  std::stack<Piece *> dead_white_pieces{};
  std::stack<Piece *> dead_black_pieces{};

private:
  void init_board();

public:
  inline Board() { this->init_board(); }
  ~Board() = default;

  void draw_board(std::vector<int> &next_possible_moves, bool &moving,
                  Color &current_player,
                  // bool &this_tile_is_a_possible_move,
                  ImFont *main_font,
                  std::optional<int> &selected_piece_position);
  void draw_tile(int i, Piece *piece, ImFont *main_font,
                 bool &is_a_possible_move,
                 std::vector<int> &next_possible_moves, bool &moving,
                 Color &current_player,
                 std::optional<int> &selected_piece_position);
  void handle_tile_click(int index, Piece *piece, bool &is_a_possible_move,
                         std::vector<int> &next_possible_moves, bool &moving,
                         Color &current_player,
                         std::optional<int> &selected_piece_position);
  void click_playable_piece(int index, std::vector<int> &next_possible_moves,
                            bool &moving,
                            std::optional<int> &selected_piece_position);
  void click_reachable_tile(int index, std::vector<int> &next_possible_moves,
                            bool &moving, Color &current_player,
                            std::optional<int> &selected_piece_position);

  const std::array<Piece *, 64> &get_positions_board() const {
    return this->positions_board;
  }

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