#pragma once
#include "./pieces/Piece.hpp"
#include "Board.hpp"
#include <array>
#include <iostream>
#include <vector>

inline std::pair<int, int> get_pos_2D(int pos1D) {
  return std::make_pair(pos1D / 8, pos1D % 8);
}
inline int get_pos_1D(std::pair<int, int> pos2D) {
  return pos2D.first * 8 + pos2D.second;
}

void display_vector_pos(std::vector<int> &possible_moves);

// ----------------- TOWER/BISHOP/QUEEN/KING -----------------

void get_linear_moves(std::vector<int> &moves, const Board &board,
                      const Direction &direction,
                      const std::pair<int, int> &position, Color color,
                      bool king = false);

void get_up_right_moves(std::vector<int> &moves, const Board &board,
                        const std::pair<int, int> &position, Color color,
                        bool king);
void get_up_left_moves(std::vector<int> &moves, const Board &board,
                       const std::pair<int, int> &position, Color color,
                       bool king);
void get_down_right_moves(std::vector<int> &moves, const Board &board,
                          const std::pair<int, int> &position, Color color,
                          bool king);
void get_down_left_moves(std::vector<int> &moves, const Board &board,
                         const std::pair<int, int> &position, Color color,
                         bool king);
void get_up_moves(std::vector<int> &moves, const Board &board,
                  const std::pair<int, int> &position, Color color, bool king);
void get_down_moves(std::vector<int> &moves, const Board &board,
                    const std::pair<int, int> &position, Color color,
                    bool king);
void get_right_moves(std::vector<int> &moves, const Board &board,
                     const std::pair<int, int> &position, Color color,
                     bool king);
void get_left_moves(std::vector<int> &moves, const Board &board,
                    const std::pair<int, int> &position, Color color,
                    bool king);

// ----------------- KNIGHT -----------------

void get_knight_tile_from_step(std::vector<int> &moves, const Board &board,
                               const std::pair<int, int> &position, Color color,
                               int stepX, int stepY);

// ----------------- PAWN -----------------

void get_pawn_moves(std::vector<int> &moves, const Board &board,
                    const std::pair<int, int> &position, Color color,
                    bool first_move);