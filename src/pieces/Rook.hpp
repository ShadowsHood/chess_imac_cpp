#pragma once
#include <array>
#include <iostream>
#include "./Piece.hpp"

class Rook : public Piece {
    
    public:
        Rook(Color color) : Piece(color, Type::Rook) {};
        virtual ~Rook() = default;

        std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) override;
};