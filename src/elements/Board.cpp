#include "./Board.hpp"
#include "./Piece.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/King.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Pawn.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/Rook.hpp"

#include "./pieces/bonus/Fool.hpp"
#include "./pieces/bonus/Racist.hpp"
#include "./pieces/bonus/Elevator.hpp"

#include "./random/random.hpp"
#include "utils.hpp"
#include <draw.hpp>
#include <iostream>
#include "pieces/bonus/Kamikaze.hpp"

void Board::init_board() {

  this->current_player = Color::White;
  this->moving = false;
  this->selected_piece_position.reset();
  this->next_possible_moves.clear();
  this->index_en_passant_available = -1;

  this->chess_board[get_pos_1D(std::make_pair(0, 0))] =
      std::make_unique<Rook>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(0, 1))] =
      std::make_unique<Knight>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(0, 2))] =
      std::make_unique<Bishop>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(0, 3))] =
      std::make_unique<Queen>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(0, 4))] =
      std::make_unique<King>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(0, 5))] =
      std::make_unique<Bishop>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(0, 6))] =
      std::make_unique<Knight>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(0, 7))] =
      std::make_unique<Rook>(Color::Black);

  this->chess_board[get_pos_1D(std::make_pair(1, 0))] =
      std::make_unique<Pawn>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(1, 1))] =
      std::make_unique<Pawn>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(1, 2))] =
      std::make_unique<Pawn>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(1, 3))] =
      std::make_unique<Pawn>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(1, 4))] =
      std::make_unique<Pawn>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(1, 5))] =
      std::make_unique<Pawn>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(1, 6))] =
      std::make_unique<Pawn>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(1, 7))] =
      std::make_unique<Pawn>(Color::Black);

  this->chess_board[get_pos_1D(std::make_pair(6, 0))] =
      std::make_unique<Pawn>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(6, 1))] =
      std::make_unique<Pawn>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(6, 2))] =
      std::make_unique<Pawn>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(6, 3))] =
      std::make_unique<Pawn>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(6, 4))] =
      std::make_unique<Pawn>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(6, 5))] =
      std::make_unique<Pawn>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(6, 6))] =
      std::make_unique<Pawn>(Color::Black);
  this->chess_board[get_pos_1D(std::make_pair(6, 7))] =
      std::make_unique<Pawn>(Color::White);

  this->chess_board[get_pos_1D(std::make_pair(7, 0))] =
      std::make_unique<Rook>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(7, 1))] =
      std::make_unique<Knight>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(7, 2))] =
      std::make_unique<Fool>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(7, 3))] =

      std::make_unique<Queen>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(7, 4))] =
      std::make_unique<King>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(7, 5))] =
      std::make_unique<Bishop>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(7, 6))] =
      std::make_unique<Knight>(Color::White);
  this->chess_board[get_pos_1D(std::make_pair(7, 7))] =
      std::make_unique<Rook>(Color::White);
}

std::vector<Piece const *> Board::get_dead_pieces(Color color) const {
  const std::vector<std::unique_ptr<Piece>> &source =
      (color == Color::White ? this->dead_white_pieces
                             : this->dead_black_pieces);

  std::vector<Piece const *> result;
  result.reserve(source.size()); // Optional: Reserve space for efficiency

  for (const auto &piece_ptr : source) {
    if (piece_ptr) {
      result.push_back(piece_ptr.get());
    }
  }
  return result;
};

std::unique_ptr<Piece> Board::take_piece(Piece *piece) {
  for (int i = 0; i < 64; ++i) {
    if (chess_board[i].get() == piece) {
      std::unique_ptr<Piece> taken_piece = std::move(chess_board[i]);
      chess_board[i] = nullptr;
      return taken_piece;
    }
  }
  return nullptr;
}

void Board::set_piece(std::unique_ptr<Piece> piece, int position) {
  this->chess_board[position] = std::move(piece);
};

bool Board::is_in_board(std::pair<int, int> position) const {
  return (position.first >= 0 && position.first < 8) && position.second >= 0 &&
         position.second < 8;
}

void Board::kill_piece(int position) {
  if (chess_board[position]) {
    std::unique_ptr<Piece> piece = std::move(chess_board[position]);

    // Game over
    if (piece->get_type() == Type::King) {
      in_game = false;
      std::cout << "Game over\n";
    }

    if (piece->get_color() == Color::White) {
      dead_white_pieces.push_back(std::move(piece));
    } else {
      dead_black_pieces.push_back(std::move(piece));
    }
    chess_board[position] = nullptr;
  }
}

void Board::handle_tile_click(int index, Piece const *piece,
                              bool &is_a_possible_move) {

  if (!this->is_empty(index) && piece->get_color() == current_player &&
      index != selected_piece_position) { // Si la  case est valide
    // Si je clique sur une pièce jouable
    click_playable_piece(index);

  } else if (index == selected_piece_position) {
    // Si je clique sur la même pièce
    deselect_piece();
  } else if (moving && is_a_possible_move && selected_piece_position) {

    // Si je clique sur une case ou je peux me déplacer
    click_reachable_tile(index);

  } else { // Si la case est erronée
    if ((is_empty(index))) {
      // Si je clique sur une case vide
      deselect_piece();
    } else if (!moving && piece->get_color() != current_player) {
      // Si je clique sur une pièce non jouable
      std::cout << "Not your turn\n";
    } else {
      // Si je clique sur une case non jouable et imprévue
      deselect_piece();
      std::cout << "Invalid move\n";
    }
  }
}

void Board::click_playable_piece(int index) {
  // std::cout << "Clicked tile : " << index << " ==> (" << get_pos_2D(index).first
  //           << "," << get_pos_2D(index).second << ") \n";
  moving = true;
  selected_piece_position = index;
  next_possible_moves =
      this->chess_board[index]->get_possible_moves(*this, index);

  // Gestion du Fool
  if (this->chess_board[index]->get_type() == Type::Fool) {
    if (dynamic_cast<Fool *>(this->chess_board[index].get())->canMove()) {
      int i{Random::random_int(
          0, static_cast<int>(next_possible_moves.size() - 1))};
      click_reachable_tile(next_possible_moves[i]);
    } else {
      std::cout << "cheh" << '\n';
      end_turn();
    }
  } 
  // Gestion du Elevator
  else if (this->chess_board[index]->get_type() == Type::Elevator) {
    Elevator *elevator = dynamic_cast<Elevator *>(this->chess_board[index].get());
    int jump = next_possible_moves[0];
    click_reachable_tile(index + (8*jump));
    if (index + (8*jump) < 8 || index + (8*jump) > 55) {
      elevator->switch_direction();
    }
  }
}

void Board::click_reachable_tile(int index) {
  this->chess_board[*selected_piece_position]->move(
      *this, *selected_piece_position, index);
  end_turn();
}

void Board::end_turn() {
  moving = false;
  if (!promotion_activated)
    selected_piece_position.reset();
  next_possible_moves.clear();
  current_player = (current_player == Color::White) ? Color::Black : Color::White;

  // Update kamiakazes time before explosion
  if (current_player == Color::White && !active_kamikazes.empty()) {
    for (auto it = active_kamikazes.begin(); it != active_kamikazes.end();) {
      (*it)->update_time_before_explosion(*this);
      if ((*it)->get_time_before_explosion() <= 0) {
        (*it)->explode(*this);
        it = active_kamikazes.erase(it);
      } else {
        ++it;
      }
    }  
  }
}

void Board::deselect_piece() {
  moving = false;
  selected_piece_position.reset();
  next_possible_moves.clear();
}

void Board::handle_promotion(ImFont *main_font) {
  ImGui::OpenPopup("Promotion of your pawn");
  if (this->is_promotion_activated()) {
    char new_type = draw_promotion_popup(main_font, current_player);
    if (new_type != '\0') {
      this->chess_board[*selected_piece_position]->promotion(
          *this, selected_piece_position.value(), new_type);
      promotion_activated = false;
      selected_piece_position.reset();
    }
  }
}

void Board::add_kamikaze(Kamikaze *kamikaze) {
  this->active_kamikazes.push_back(kamikaze);
}

int Board::get_piece_position(const Piece* piece) const {
  for (int i = 0; i < 64; ++i) {
      if (chess_board[i] && chess_board[i].get() == piece) {
          return i;
      }
  }
  return -1;
}