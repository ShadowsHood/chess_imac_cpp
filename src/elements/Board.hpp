#pragma once
#include "./Piece.hpp"
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
  int index_en_passant_available{};
  bool in_game{true};
  bool promotion_activated{false};

private:
  void init_board();

public:
  Board() { this->init_board(); }

  Piece *operator[](int position) const {
    return this->positions_board[position] ? this->positions_board[position]
                                           : nullptr;
  };

  // Actions click
  void handle_tile_click(int index, Piece *piece, bool &is_a_possible_move);
  void click_playable_piece(int index);
  void click_reachable_tile(int index);

  // En passant
  bool en_passant_available(int position) const {
    return this->index_en_passant_available == position;
  };
  int get_en_passant_available() const {
    return this->index_en_passant_available;
  };
  void set_en_passant_available(int position) {
    this->index_en_passant_available = position;
  };

  // Getters
  std::vector<int> get_next_possible_moves() const {
    return this->next_possible_moves;
  };
  std::stack<Piece *> get_dead_white_pieces() const {
    return this->dead_white_pieces;
  };
  std::stack<Piece *> get_dead_black_pieces() const {
    return this->dead_black_pieces;
  };
  std::optional<int> get_selected_piece_position() const {
    return this->selected_piece_position;
  };
  bool get_in_game() const { return this->in_game; };

  // Setters
  void set_selected_piece_position(int position) {
    this->selected_piece_position.emplace(position);
  };

  // Promotion
  bool is_promotion_activated() const { return this->promotion_activated; };
  void set_promotion_activated(bool b) { this->promotion_activated = b; };
  void handle_promotion(ImFont *main_font);

  // Utils
  void deselect_piece();
  void set_piece(Piece *piece, int position);
  void kill_piece(Piece *piece, Color color, int position);
  bool is_in_board(std::pair<int, int> position) const;
  bool is_empty(int position) const {
    return this->positions_board[position] == nullptr;
  };
  bool is_other_color(int position, Color color) const {
    return this->positions_board[position]->get_color() != color;
  };
};