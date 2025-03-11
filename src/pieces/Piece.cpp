#include "./Piece.hpp"
#include "./Board.hpp"
#include <iostream>
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"

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

  // Transformation of the pawn
  if (this->type == Type::Pawn && (new_position / 8 == 0 || new_position / 8 == 7)) {
    this->transform_pawn(board, new_position);
  }
}

void Piece::transform_pawn(Board & board, int new_position) {
  std::cout << "In wich piece do you want to transform the pawn ? \nQueen (q), Rook (r), Bishop (b), Knight (k) \n";
  char type;
  std::cin >> type;
  
  if (type == 'q') {
    Queen* q = new Queen(this->color);
    board.set_piece(q, new_position);
  } else if (type == 'r') {
    Rook* r = new Rook(this->color);
    board.set_piece(r, new_position);
  } else if (type == 'b') {
    Bishop* b = new Bishop(this->color);
    board.set_piece(b, new_position);
  } else if (type == 'k') {
    Knight* k = new Knight(this->color);
    board.set_piece(k, new_position);
  } else {
    std::cout << "Invalid type \n";
    return;
  }
  delete this;    
}