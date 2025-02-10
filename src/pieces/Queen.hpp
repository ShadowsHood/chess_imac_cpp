#pragma once
#include <iostream>
#include <array>
#include "./Piece.hpp"

class Queen : public Piece {

    public:
        Queen(Color color) : Piece(color, Type::Queen) {};
        virtual ~Queen() = default;

        std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) override;
};