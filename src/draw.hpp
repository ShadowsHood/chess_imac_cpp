#pragma once
#include "board.hpp"
#include <imgui.h>
#include <vector>

ImVec4 get_tile_color(int i);

bool is_possible_move(std::vector<int> &next_possible_moves, int i);

void push_font(Piece *piece, ImFont *&main_font);
void pop_font();

void push_possible_move_color();
void pop_possible_move_color();

void set_background_color();