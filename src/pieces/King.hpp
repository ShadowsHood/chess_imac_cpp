#pragma once
#include <iostream>
#include <array>
#include "./Piece.hpp"

class King : public Piece {

    public:
        King(Color color) : Piece(color, Type::King) {};
        virtual ~King() = default;

        std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) override;
};