#include "./Piece.hpp"
#include "./Board.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/Rook.hpp"

#include "./pieces/bonus/Fool.hpp"
#include "./pieces/bonus/Kamikaze.hpp"
#include "./pieces/bonus/Racist.hpp"
#include "./pieces/bonus/Well.hpp"

#include "utils.hpp"
#include <random/random.hpp>
#include <iostream>
#include <thread>

void Piece::move(Board &board, int old_position, int new_position) {

  std::pair<int, int> old_pos_2D = get_pos_2D(old_position);
  std::pair<int, int> new_pos_2D = get_pos_2D(new_position);

  if (type == Type::Pawn || type == Type::Kamikaze) {
    handle_en_passant(board, new_pos_2D);
  }

  update_en_passant_availability(board, new_pos_2D, new_position);

  if (first_move)
    first_move = false;
  if (type == Type::Kamikaze)
    dynamic_cast<Kamikaze *>(this)->init_time_before_explosion(board);

  if (!board.is_empty(new_position)) {
    board.kill_piece(new_position);
  }

  std::unique_ptr<Piece> piece = board.take_piece(this);
  if (piece) {
    board.set_piece(std::move(piece), new_position);
  } else {
    std::cerr << "Error: Piece not found on the board." << '\n';
  }

  // Promotion
  if (this->type == Type::Pawn &&
      (new_position / 8 == 0 || new_position / 8 == 7)) {
    board.set_promotion_activated(true);
    board.set_selected_piece_position(new_position);
  }

  // Random on sound
  if (this->type != Type::Fool && this->type != Type::Kamikaze &&
      Random::bernoulli_law(0.5))
    std::thread(play_sound, this->sound).detach();
}

void Piece::handle_en_passant(Board &board,
                              std::pair<int, int> new_pos_2D) const {
  const int invalid = -1;
  int en_passant_available = board.get_en_passant_available();
  if (en_passant_available == invalid)
    return;

  std::pair<int, int> en_passant_2D = get_pos_2D(en_passant_available);
  int direction = (get_color() == Color::White) ? 1 : -1;
  bool same_x = (en_passant_2D.second == new_pos_2D.second);
  bool good_offset_y = (en_passant_2D.first == new_pos_2D.first + direction);
  // std::cout << "En passant : " << en_passant_2D.first << " " << en_passant_2D.second << '\n';
  // std::cout << "Destination : " << new_pos_2D.first << " " << new_pos_2D.second << '\n';

  if (same_x && good_offset_y) {
    if (board[en_passant_available]->get_color() != this->get_color()) {
      board.kill_piece(en_passant_available);
    }
  }
}

void Piece::update_en_passant_availability(Board &board,
                                           std::pair<int, int> new_pos_2D,
                                           int new_position) {
  if ((type == Type::Pawn || type == Type::Kamikaze) && first_move &&
      (new_pos_2D.first == 3 || new_pos_2D.first == 4)) {
    board.set_en_passant_available(new_position);
  } else {
    board.set_en_passant_available(-1);
  }
}

void Piece::promotion(Board &board, int position, char type) {
  std::thread(play_sound, "promotion.mp3").detach();
  Piece *new_piece = nullptr;

  switch (type) {
  case 'r':
    new_piece = std::make_unique<Rook>(this->color).release();
    break;
  case 'b':
    new_piece = std::make_unique<Bishop>(this->color).release();
    break;
  case 'k':
    new_piece = std::make_unique<Knight>(this->color).release();
    break;
  case 'n':
    new_piece = std::make_unique<Racist>(this->color).release();
    break;
  case 'f':
    new_piece = std::make_unique<Fool>(this->color).release();
    break;
  case 'w':
    new_piece = std::make_unique<Well>(this->color).release();
    break;
  default:
    new_piece = std::make_unique<Queen>(this->color).release();
    break;
  }

  if (new_piece != nullptr) {
    board.set_piece(std::unique_ptr<Piece>(new_piece), position);
  } else {
    std::cerr << "Promotion Fatal Error" << '\n';
  }
}