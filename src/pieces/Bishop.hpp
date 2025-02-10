#pragma once
#include <iostream>
#include <array>
#include "./Piece.hpp"

class Bishop : public Piece {

    public:
        Bishop(Color color) : Piece(color, Type::Bishop) {this->set_char(color, Type::Bishop);};
        virtual ~Bishop() = default;

        std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) override;
};