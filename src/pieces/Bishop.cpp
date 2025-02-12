#include "./Bishop.hpp"
#include "./utils.hpp"

std::vector<int> Bishop::get_possible_moves(const Board & board, int position)  {
        std::cout << "------------entree fonction" << std::endl;
    std::vector<int> possible_moves;
    get_up_right_moves(possible_moves, board, get_pos_2D(position), this->color, false);
        std::cout << "------------fin up right" << std::endl;
    get_up_left_moves(possible_moves, board, get_pos_2D(position), this->color, false);
        std::cout << "------------fin up left" << std::endl;
    get_down_right_moves(possible_moves, board, get_pos_2D(position), this->color, false);
        std::cout << "------------fin down right" << std::endl;
    get_down_left_moves(possible_moves, board, get_pos_2D(position), this->color, false);
        std::cout << "------------fin down left" << std::endl;

    for (int pos : possible_moves) {
        std::cout << pos << " - ";
    }
    std::cout << std::endl;
    return possible_moves;
}