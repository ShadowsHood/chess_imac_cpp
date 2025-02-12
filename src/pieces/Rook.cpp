#include "./Rook.hpp"
#include "./utils.hpp"

std::vector<int> Rook::get_possible_moves(const Board & board, int position) 
{
    std::vector<int> possible_moves;

    get_up_moves(possible_moves, board, get_pos_2D(position), this->color, false);
    get_right_moves(possible_moves, board, get_pos_2D(position), this->color, false);
    get_down_moves(possible_moves, board, get_pos_2D(position), this->color, false);
    get_left_moves(possible_moves, board, get_pos_2D(position), this->color, false);

    return possible_moves;
}