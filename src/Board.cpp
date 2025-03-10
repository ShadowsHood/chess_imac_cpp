#include "./Board.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/King.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Pawn.hpp"
#include "./pieces/Piece.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/Rook.hpp"
#include "utils.hpp"

void Board::init_board() {

  this->current_player = Color::White;
  this->moving = false;
  this->selected_piece_position.reset();
  this->next_possible_moves.clear();

  this->positions_board[get_pos_1D(std::make_pair(0, 0))] =
      new Rook(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(0, 1))] =
      new Knight(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(0, 2))] =
      new Bishop(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(0, 3))] =
      new Queen(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(0, 4))] =
      new King(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(0, 5))] =
      new Bishop(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(0, 6))] =
      new Knight(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(0, 7))] =
      new Rook(Color::Black);

  this->positions_board[get_pos_1D(std::make_pair(1, 0))] =
      new Pawn(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(1, 1))] =
      new Pawn(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(1, 2))] =
      new Pawn(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(1, 3))] =
      new Pawn(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(1, 4))] =
      new Pawn(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(1, 5))] =
      new Pawn(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(1, 6))] =
      new Pawn(Color::Black);
  this->positions_board[get_pos_1D(std::make_pair(1, 7))] =
      new Pawn(Color::Black);

  this->positions_board[get_pos_1D(std::make_pair(6, 0))] =
      new Pawn(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(6, 1))] =
      new Pawn(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(6, 2))] =
      new Pawn(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(6, 3))] =
      new Pawn(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(6, 4))] =
      new Pawn(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(6, 5))] =
      new Pawn(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(6, 6))] =
      new Pawn(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(6, 7))] =
      new Pawn(Color::White);

  this->positions_board[get_pos_1D(std::make_pair(7, 0))] =
      new Rook(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(7, 1))] =
      new Knight(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(7, 2))] =
      new Bishop(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(7, 3))] =
      new Queen(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(7, 4))] =
      new King(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(7, 5))] =
      new Bishop(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(7, 6))] =
      new Knight(Color::White);
  this->positions_board[get_pos_1D(std::make_pair(7, 7))] =
      new Rook(Color::White);
}

void Board::set_piece(Piece *piece, int position) {
  this->positions_board[position] = piece;
};

bool Board::is_in_board(std::pair<int, int> position) const {
  return (position.first >= 0 && position.first < 8) && position.second >= 0 &&
         position.second < 8;
}

void Board::kill_piece(Piece *piece, Color color, int position) {
  if (color == Color::White) {
    this->dead_white_pieces.push(piece);
  } else {
    this->dead_black_pieces.push(piece);
  }
  this->positions_board[position] = nullptr;
}

void Board::handle_tile_click(int index, Piece *piece, bool &is_a_possible_move) {
  if (!moving && piece->get_color() != current_player)
    std::cout << "Not your turn\n";
  // Si je clique  sur une pièce jouable
  if (!this->is_empty(index) && piece->get_color() == current_player) {
    click_playable_piece(index);
    // Si je clique sur une case ou je peux me déplacer
  } else if (moving && is_a_possible_move && selected_piece_position) {
    click_reachable_tile(index);
  } else {
    deselect_piece();
    // std::cout << "Invalid move" << std::endl;
  }
}

void Board::click_playable_piece(int index) {
  std::cout << "Clicked tile : " << index << " ==> (" << get_pos_2D(index).first
            << "," << get_pos_2D(index).second << ") \n";
  moving = true;
  selected_piece_position = index;
  next_possible_moves =
      this->get_piece(index)->get_possible_moves(*this, index);
}

void Board::click_reachable_tile(int index) {
  this->get_piece(*selected_piece_position)
      ->move(*this, *selected_piece_position, index);
  moving = false;
  selected_piece_position.reset();
  next_possible_moves.clear();
  current_player =
      (current_player == Color::White) ? Color::Black : Color::White;
}

void Board::deselect_piece() {
  moving = false;
  selected_piece_position.reset();
  next_possible_moves.clear();
}