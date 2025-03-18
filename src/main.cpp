#include "./draw.hpp"
#include "./elements/Board.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "./3d/test.hpp"


int main() {
  Board board;

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
  ImFont *main_font = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 60.0f);
  IM_ASSERT(main_font != nullptr);

  quick_imgui::loop(
    "Quick ImGui",
    {
        .init                     = []() { std::cout << "Init\n"; },
        .loop                     = [&board, main_font]() {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                board.deselect_piece();

            ImGui::Begin("Chess Game");
            ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);
            set_background_color();

            // Draw the board
            draw_dead_pieces(board, Color::White, main_font);
            draw_board(board, main_font);
            ImGui::Spacing();
            draw_dead_pieces(board, Color::Black, main_font);

            ImGui::End();
            test_triangle();
        },
        .key_callback             = [](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
        .mouse_button_callback    = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
        .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
        .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
        .window_size_callback     = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
    }
  );
}
