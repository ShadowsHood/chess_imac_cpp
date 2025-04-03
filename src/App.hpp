#pragma once
#include "./3d/Renderer3d.hpp"
#include "./draw.hpp"
#include "./elements/Board.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

class App {
public:
  Board board;
  ImFont *main_font{};
  Renderer3d renderer3d;

  App() = default;
  void launch();

private:
  void init_font();
  void chess_2d();
};