#include "./Piece.hpp"
#include "./Board.hpp"
#include "../Draw.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/Rook.hpp"

#include "./pieces/bonus/Racist.hpp"
#include "./pieces/bonus/Fool.hpp"
#include "./pieces/bonus/Kamikaze.hpp"
#include "pieces/bonus/Elevator.hpp"

#include "utils.hpp"
#include <iostream>
#include <thread>
#include <random/random.hpp>

void Piece::move(Board &board, int old_position, int new_position) {

  std::pair<int, int> old_pos_2D = get_pos_2D(old_position);
  std::pair<int, int> new_pos_2D = get_pos_2D(new_position);

  if (type == Type::Pawn) {
    handleEnPassant(board, new_pos_2D);
  }

  updateEnPassantAvailability(board, new_pos_2D, new_position);

  if (first_move)
    first_move = false;

  if (!board.is_empty(new_position)) {
    board.kill_piece(new_position);
  }

  // board.set_piece(nullptr, old_position);
  std::unique_ptr<Piece> piece = board.take_piece(this);
  if (piece) {
    board.set_piece(std::move(piece), new_position);
  } else {
    std::cerr << "Error: Piece not found on the board." << '\n';
  }

  // Promotion
  if (this->type == Type::Pawn && (new_position / 8 == 0 || new_position / 8 == 7)) {
    board.set_promotion_activated(true);
    board.set_selected_piece_position(new_position);
  }

  // Random on sound
  if (Random::bernoulli_law(0.5))
    std::thread(play_sound, "move.wav").detach();
}

void Piece::handleEnPassant(Board &board, std::pair<int, int> new_pos_2D) {
  const int invalid = -1;
  int en_passant_available = board.get_en_passant_available();
  std::pair<int, int> en_passant_available_pos_2D =
      (en_passant_available != invalid) ? get_pos_2D(en_passant_available)
                                        : std::make_pair(invalid, invalid);

  if ((new_pos_2D.first - 1 == en_passant_available_pos_2D.first ||
       new_pos_2D.first + 1 == en_passant_available_pos_2D.first) &&
      new_pos_2D.second == en_passant_available_pos_2D.second) {
        if (board[en_passant_available]->get_color() != this->get_color()) {
          board.kill_piece(en_passant_available);
      }
  }
}

void Piece::updateEnPassantAvailability(Board &board,
                                        std::pair<int, int> new_pos_2D,
                                        int new_position) {
  if (type == Type::Pawn && first_move &&
      (new_pos_2D.first == 3 || new_pos_2D.first == 4)) {
    board.set_en_passant_available(new_position);
  } else {
    board.set_en_passant_available(-1);
  }
}

void Piece::promotion(Board &board, int position, char type) { 
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
    case 'z':
      new_piece = std::make_unique<Kamikaze>(this->color).release();
      break;
    case 'w':
      new_piece = std::make_unique<Elevator>(this->color).release();
      break;
    default:
      new_piece = std::make_unique<Queen>(this->color).release();
      break;
  }

  if (new_piece != nullptr) {
      board.set_piece(std::unique_ptr<Piece>(new_piece), position);
      if (new_piece->get_type() == Type::Kamikaze) {
        board.add_kamikaze(dynamic_cast<Kamikaze*>(new_piece));
      }
  } else {
      std::cerr << "Promotion Fatal Error" << std::endl;
  }
}