#pragma once
#include "./pieces/Piece.hpp"
#include <array>
#include <iostream>
#include <vector>
#include "Board.hpp"

inline std::pair<int, int> get_pos_2D(int pos1D) {
  return std::make_pair(pos1D / 8, pos1D % 8);
}
inline int get_pos_1D(std::pair<int, int> pos2D) {
  return pos2D.first * 8 + pos2D.second;
}

void get_step_from_direction(const Direction &direction, int &stepX,
                             int &stepY);

void get_linear_moves(std::vector<int> &moves,const Board &board,
                      const Direction &direction,
                      const std::pair<int, int> &position, Color color,
                      bool king = false);

void get_up_right_moves(std::vector<int> &moves,const Board &board,
                        const std::pair<int, int> &position, Color color,
                        bool king);
void get_up_left_moves(std::vector<int> &moves,const Board & board,
                       const std::pair<int, int> &position, Color color,
                       bool king);
void get_down_right_moves(std::vector<int> &moves,const Board & board,
                          const std::pair<int, int> &position, Color color,
                          bool king);
void get_down_left_moves(std::vector<int> &moves,const Board & board,
                         const std::pair<int, int> &position, Color color,
                         bool king);
void get_up_moves(std::vector<int> &moves,
                  const Board & board,
                  const std::pair<int, int> &position, Color color, bool king);
void get_down_moves(std::vector<int> &moves,
                    const Board & board,
                    const std::pair<int, int> &position, Color color,
                    bool king);
void get_right_moves(std::vector<int> &moves,
                     const Board & board,
                     const std::pair<int, int> &position, Color color,
                     bool king);
void get_left_moves(std::vector<int> &moves,
                    const Board & board,
                    const std::pair<int, int> &position, Color color,
                    bool king);