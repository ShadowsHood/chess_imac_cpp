#include "./Piece.hpp"
#include "./Board.hpp"

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

void Piece::move(Board & board, int old_position, int new_position) {
  this->first_move = false;
  if (!board.is_empty(new_position)) {
    board.kill_piece(board.get_piece(new_position), board.get_piece(new_position)->get_color(), new_position);
  } 
  board.set_piece(nullptr, old_position);
  board.set_piece(this, new_position);
}