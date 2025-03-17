#pragma once
#include "./Piece.hpp"
#include <array>
#include <imgui.h>
#include <memory>
#include <optional>
#include <vector>

class Board {
private:
  std::array<std::unique_ptr<Piece>, 64> chess_board{};
  std::vector<std::unique_ptr<Piece>> dead_white_pieces{};
  std::vector<std::unique_ptr<Piece>> dead_black_pieces{};

  Color current_player{};
  std::vector<int> next_possible_moves{};
  std::optional<int> selected_piece_position{};
  bool moving{};
  int index_en_passant_available{};
  bool in_game{true};

private:
  void init_board();

public:
  Board() { this->init_board(); }

  Piece const *operator[](int position) const {
    return this->chess_board[position].get();
  };

  // Actions click
  void handle_tile_click(int index, Piece const *piece,
                         bool &is_a_possible_move);
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
  std::vector<Piece const *> get_dead_pieces(Color color) const;
  bool get_in_game() const { return this->in_game; };

  // Utils
  void deselect_piece();
  std::unique_ptr<Piece> take_piece(Piece *piece);
  void set_piece(std::unique_ptr<Piece> piece, int position);
  void kill_piece(int position);
  bool is_in_board(std::pair<int, int> position) const;
  bool is_empty(int position) const {
    return this->chess_board[position] == nullptr;
  };
  bool is_other_color(int position, Color color) const {
    return this->chess_board[position]->get_color() != color;
  };
};