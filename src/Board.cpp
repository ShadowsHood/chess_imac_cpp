#include "./Board.hpp"
#include "utils.hpp"
#include "./pieces/Piece.hpp"
#include "./pieces/Rook.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/King.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Pawn.hpp"
#include "./pieces/Queen.hpp"

void Board::init_board() {
    this->positions_board[get_pos_1D(std::make_pair(0,0))] = new Rook(Color::Black); 
    this->positions_board[get_pos_1D(std::make_pair(0,1))] = new Knight(Color::Black); 
    this->positions_board[get_pos_1D(std::make_pair(0,2))] = new Bishop(Color::Black); 
    this->positions_board[get_pos_1D(std::make_pair(0,3))] = new Queen(Color::Black); 
    this->positions_board[get_pos_1D(std::make_pair(0,4))] = new King(Color::Black); 
    this->positions_board[get_pos_1D(std::make_pair(0,5))] = new Bishop(Color::Black); 
    this->positions_board[get_pos_1D(std::make_pair(0,6))] = new Knight(Color::Black); 
    this->positions_board[get_pos_1D(std::make_pair(0,7))] = new Rook(Color::Black); 
    
    this->positions_board[get_pos_1D(std::make_pair(1,0))] = new Pawn(Color::Black);
    this->positions_board[get_pos_1D(std::make_pair(1,1))] = new Pawn(Color::Black);
    this->positions_board[get_pos_1D(std::make_pair(1,2))] = new Pawn(Color::Black);
    this->positions_board[get_pos_1D(std::make_pair(1,3))] = new Pawn(Color::Black);
    this->positions_board[get_pos_1D(std::make_pair(1,4))] = new Pawn(Color::Black);
    this->positions_board[get_pos_1D(std::make_pair(1,5))] = new Pawn(Color::Black);
    this->positions_board[get_pos_1D(std::make_pair(1,6))] = new Pawn(Color::Black);
    this->positions_board[get_pos_1D(std::make_pair(1,7))] = new Pawn(Color::Black); 
    
    this->positions_board[get_pos_1D(std::make_pair(6,0))] = new Pawn(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(6,1))] = new Pawn(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(6,2))] = new Pawn(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(6,3))] = new Pawn(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(6,4))] = new Pawn(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(6,5))] = new Pawn(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(6,6))] = new Pawn(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(6,7))] = new Pawn(Color::White);  

    this->positions_board[get_pos_1D(std::make_pair(7,0))] = new Rook(Color::White); 
    this->positions_board[get_pos_1D(std::make_pair(7,1))] = new Knight(Color::White); 
    this->positions_board[get_pos_1D(std::make_pair(7,2))] = new Bishop(Color::White);
    this->positions_board[get_pos_1D(std::make_pair(7,3))] = new Queen(Color::White);  
    this->positions_board[get_pos_1D(std::make_pair(7,4))] = new King(Color::White); 
    this->positions_board[get_pos_1D(std::make_pair(7,5))] = new Bishop(Color::White); 
    this->positions_board[get_pos_1D(std::make_pair(7,6))] = new Knight(Color::White); 
    this->positions_board[get_pos_1D(std::make_pair(7,7))] = new Rook(Color::White); 
}

void Board::set_piece(Piece *piece, int position) {

};

bool Board::is_in_board(std::pair<int,int> position) const {
    return (position.first >= 0 && position.first < 8) && position.second >= 0 && position.second < 8;
}