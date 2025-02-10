#include "./Rook.hpp"

std::vector<int> Rook::get_possible_moves(const std::array<Piece*, 64>& positions_board, int position) 
{
    // Right check
    // {
        std::vector<int> possible_moves;
        // int              i           = position + 1;
        // bool             is_occupied = false;

        // while (i % 8 > position % 8 && !is_occupied)
        // {
        //     if (positions_board[i] != nullptr)
        //     {
        //         if ((*positions_board[i]).get_color() != this->color)
        //             possible_moves.push_back((*positions_board[i]).get_position());
        //         else
        //             is_occupied = true;
        //         i++;
        //     }
        // }
        return possible_moves;
    // }

    // Left check
    // {
    //     std::vector<int> possible_moves;
    //     int              i           = this->position - 1;
    //     bool             is_occupied = false;

    //     while (i > this->position - 7 && i % 8 < this->position % 8 && !is_occupied)
    //     {
    //         if (positions_board[i] != nullptr)
    //         {
    //             if ((*positions_board[i]).get_color() != this->color)
    //                 possible_moves.push_back((*positions_board[i]).get_position());
    //             else
    //                 is_occupied = true;
    //             i--;
    //         }
    //     }
    //     return possible_moves;
    // }
}