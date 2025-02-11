#pragma once
#include <iostream>
#include <array>
#include "./Piece.hpp"

class Knight : public Piece {

    public:
        explicit Knight(Color color) : Piece(color, Type::Knight) {this->set_char(color, Type::Knight);};
        ~Knight() override = default;

        std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) override;
};