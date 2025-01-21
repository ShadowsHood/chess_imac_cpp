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

class Piece {

    protected:
        Color color;
        Type type;
        int position;

    public:
        // Piece(): color(Color::White), type(Type::Pawn), position(0) {};
        Piece(Color color, Type type, int position): color(color), type(type), position(position) {};
        virtual ~Piece() = default;

        Color get_color() const {return this->color;};
        Type get_type() const {return this->type;};
        int get_position() const {return this->position;};
        void set_position(int pos) {this->position = pos;};
        
        virtual std::vector<int> get_possible_moves(const std::vector<Piece*> &position_on_board);
        void move(std::vector<Piece*> &position_on_board, int new_position);
};