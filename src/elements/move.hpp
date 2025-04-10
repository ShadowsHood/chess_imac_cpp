#pragma once
#include "./Board.hpp"
#include "./Color.hpp"
#include "./Direction.hpp"
#include <vector>

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