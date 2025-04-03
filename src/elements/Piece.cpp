#include "./Piece.hpp"
#include "./Board.hpp"
#include "../Draw.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/Rook.hpp"

#include "./pieces/bonus/Racist.hpp"

#include "utils.hpp"
#include <iostream>

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
      new_piece = new Rook(this->color);
      break;
    case 'b':
      new_piece = new Bishop(this->color);
      break;
    case 'k':
      new_piece = new Knight(this->color);
      break;
    case 'n':
      new_piece = std::make_unique<Racist>(this->color);
      break;
    case 'q':
    default:
      new_piece = new Queen(this->color);
      break;
  }

  if (new_piece != nullptr) {
      board.set_piece(new_piece, position);
      delete this; 
  } else {
      std::cerr << "Promotion Fatal Error" << std::endl;
  }
}