#include "./Piece.hpp"
#include "./Board.hpp"
#include "utils.hpp"

void Piece::set_char(Color color, Type type) {
  switch (type) {
  case Type::Pawn:
    this->character = (color == Color::White) ? 'p' : 'o';
    break;
  case Type::Rook:
    this->character = (color == Color::White) ? 'r' : 't';
    break;
  case Type::Knight:
    this->character = (color == Color::White) ? 'h' : 'j';
    break;
  case Type::Bishop:
    this->character = (color == Color::White) ? 'b' : 'n';
    break;
  case Type::Queen:
    this->character = (color == Color::White) ? 'q' : 'w';
    break;
  case Type::King:
    this->character = (color == Color::White) ? 'k' : 'l';
    break;
  }
}

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
    board.kill_piece(board.get_piece(new_position),
                     board.get_piece(new_position)->get_color(), new_position);
  }

  board.set_piece(nullptr, old_position);
  board.set_piece(this, new_position);
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
    board.kill_piece(board.get_piece(en_passant_available),
                     board.get_piece(en_passant_available)->get_color(),
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