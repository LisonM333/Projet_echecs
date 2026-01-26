#include "./includes/board.hpp"
#include <imgui.h>
#include <iostream>
#include <ostream>
#include "quick_imgui/quick_imgui.hpp"

void Board::board_representation (){

    float value{0.f};
    unsigned int col {}; //i
    unsigned int lig {}; //j

        quick_imgui::loop(
            "Chess",
            {
                .init = [&]() {},
                .loop =
                    [&]() {
                        ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
                        ImGui::Begin("Board");

                        ImVec4 white_cases ={0.85f, 0.85f, 1.f, 1.f};
                        ImVec4 black_cases ={0.f, 0.f, 0.25f, 1.f};
                        
                        for (int i {4}; i>0; i--){

                            for (int j {1}; j<5; j++){
                        
                                ImGui::PushStyleColor(ImGuiCol_Button, white_cases);
                                col = i*2;
                                lig = j*2-1;
                                // char col = static_cast<char>(45+col);
                                // char lig = static_cast<char>(lig);
                                ImGui::PushID((col-1)*8 + lig); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << (col-1)*8 + lig << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases);
                                col = i*2;
                                lig = j*2;
                                ImGui::PushID((col-1)*8 + lig); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << (col-1)*8 + lig << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();
                            }
                            ImGui::NewLine();
                            for (int j {1}; j<5; j++){
                        
                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases);
                                col = i*2-1;
                                lig = j*2-1;
                                ImGui::PushID((col-1)*8 + lig); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << (col-1)*8 + lig << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                ImGui::PushStyleColor(ImGuiCol_Button,white_cases);
                                col = i*2-1;
                                lig = j*2;
                                ImGui::PushID((col-1)*8 + lig); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << (col-1)*8 + lig << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();
                            }
                            ImGui::NewLine();
                        }

                        


                        

                        ImGui::End();
                        ImGui::PopStyleVar(3);
                    },
            }
        );

    }