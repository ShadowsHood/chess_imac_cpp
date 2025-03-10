#pragma once
#include "./Piece.hpp"

class King : public Piece {

    public:
        explicit King(Color color) : Piece(color, Type::King) {this->set_char(color, Type::King);};
        ~King() override = default;

        std::vector<int> get_possible_moves(const Board & board, int position) override;
};