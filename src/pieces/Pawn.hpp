#pragma once
#include <iostream>
#include <array>
#include "./Piece.hpp"

class Pawn : public Piece {

    public:
        Pawn(Color color) : Piece(color, Type::Pawn) {this->set_char(color, Type::Pawn);};
        virtual ~Pawn() = default;

        std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) override;
};