#include <imgui.h>
#include <utility>
#include <iostream>
#include <vector>
#include <array>
#include "./pieces/Piece.hpp"
#include "./pieces/Rook.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/King.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Pawn.hpp"
#include "./pieces/Queen.hpp"
#include "./utils.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main()
{
    std::vector<int>       next_possible_moves;
    bool                   moving         = false;
    Color                  current_player = Color::White;
    std::array<Piece*, 64> positions_board;

    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Example");

            for (int i = 0; i < 64; i++)
            {
                ImGui::PushID(i);
                if (i % 8 != 0)
                    ImGui::SameLine();
                if ((i / 8) % 2 == 0)
                {
                    if (i % 2 == 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.8f, 0.8f, 1.f});
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.2f, 0.2f, 1.f});
                    }
                }
                else
                {
                    if (i % 2 == 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.2f, 0.2f, 1.f});
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.8f, 0.8f, 1.f});
                    }
                }

                std::string name = std::to_string((i / 8) + 1) + std::to_string((i % 8) + 1);
                if (ImGui::Button(name.c_str(), ImVec2{50.f, 50.f}))
                    std::cout << "Clicked button " << i << "\n";
                ImGui::PopStyleColor();
                ImGui::PopID();
            }

            ImGui::End();
        }
    );
}