#pragma once
#include <iostream>
#include <array>
#include "./Piece.hpp"

class King : public Piece {

    public:
        explicit King(Color color) : Piece(color, Type::King) {this->set_char(color, Type::King);};
        ~King() override = default;

        std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) override;
};