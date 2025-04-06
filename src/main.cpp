#include "./draw.hpp"
#include "./elements/Board.hpp"
#include "./random/random.hpp"
#include "quick_imgui/quick_imgui.hpp"
// #include <filesystem>

#include <imgui.h>
#include <iostream>

#include "./App.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main() {
  // std::cout << "Current working directory: " <<
  // std::filesystem::current_path()
  //           << "\n";
  App app;
  app.launch();
}
