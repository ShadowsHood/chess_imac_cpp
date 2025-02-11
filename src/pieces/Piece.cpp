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

void Piece::move(Board & board, int new_position) {}