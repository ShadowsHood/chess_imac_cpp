#pragma once
#include "./elements/Board.hpp"
#include "./elements/Piece.hpp"
#include <imgui.h>
#include <vector>

ImVec4 get_tile_color(int i);

bool is_possible_move(const std::vector<int> &next_possible_moves, int i);

void push_font(Piece *piece, ImFont *&main_font);
void pop_font();

void push_possible_move_color();
void pop_possible_move_color();

void set_background_color();

void draw_board(Board &board, ImFont *main_font);
void draw_tile(Board &board, int i, Piece *piece, ImFont *main_font,
                      bool &is_a_possible_move);
void draw_dead_pieces(const Board &board, Color color,
                             ImFont *main_font);