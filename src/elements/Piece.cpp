#include "./Piece.hpp"
#include "./Board.hpp"
#include "../Draw.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/Rook.hpp"
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
    board.kill_piece(board[new_position], board[new_position]->get_color(),
                     new_position);
  }

  board.set_piece(nullptr, old_position);
  board.set_piece(this, new_position);

  // Promotion
  if (this->type == Type::Pawn && (new_position / 8 == 0 || new_position / 8 == 7)) {
    std::cout << "BONCHOUR \n";
    ImGui::OpenPopup("Promotion of your pawn");
    char new_type = get_promotion_type_popup();
    this->promotion(board, new_position, new_type);
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
    board.kill_piece(board[en_passant_available],
                     board[en_passant_available]->get_color(),
                     en_passant_available);
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