#pragma once
#include <iostream>
#include <vector>
#include "./Piece.hpp"

class Pawn : public Piece {

    public:
        Pawn(Color color, int position): Piece(color, Type::Pawn, position) {};
        virtual ~Pawn() = default;

        std::vector<int> get_possible_moves(const std::vector<Piece*> &position_on_board) override;
};