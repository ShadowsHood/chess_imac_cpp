#pragma once
#include <iostream>
#include <vector>

enum class Color {
    White,
    Black
};
enum class Type {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum class Direction {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

class Piece {
protected:
    Color color;
    Type  type;

public:
    // Piece(): color(Color::White), type(Type::Pawn), position(0) {};
    Piece(Color color, Type type)
        : color(color), type(type){};
    virtual ~Piece() = default;

    Color get_color() const { return this->color; };
    Type  get_type() const { return this->type; };

    virtual std::vector<int> get_possible_moves(const std::array<Piece*, 64>& positions_board, int position)=0;
    void                     move(std::vector<Piece*>& position_on_board, int new_position);
};