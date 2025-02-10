#pragma once
#include "./pieces/Piece.hpp"
#include <array>
#include <iostream>
#include <vector>

class Board {

private:
  std::array<Piece *, 64> positions_board;

private :
    void init_board();

public:
    inline Board() { this->init_board(); }
    ~Board() = default;

    void set_piece(Piece* piece, int position);

    bool is_in_board(std::pair<int, int> position);
    bool is_empty(std::pair<int, int> position);
    bool is_other_color(std::pair<int, int> position, Color color);
};