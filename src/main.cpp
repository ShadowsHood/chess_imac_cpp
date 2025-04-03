#include "./draw.hpp"
#include "./elements/Board.hpp"
#include "./random/random.hpp"
#include "quick_imgui/quick_imgui.hpp"

#include <imgui.h>
#include <iostream>

#include "./App.hpp"

#define GLFW_INCLUDE_NONE
#include "./3d/test.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main() {
  App app;
  app.launch();
}
