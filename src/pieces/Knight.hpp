#pragma once
#include <iostream>
#include <array>
#include "./Piece.hpp"

class Knight : public Piece {

    public:
        explicit Knight(Color color) : Piece(color, Type::Knight) {this->set_char(color, Type::Knight);};
        ~Knight() override = default;

        std::vector<int> get_possible_moves(const Board & board, int position) override;
};