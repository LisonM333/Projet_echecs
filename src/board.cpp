#include "./includes/board.hpp"
#include <imgui.h>
#include <iostream>
#include <ostream>
#include "quick_imgui/quick_imgui.hpp"

void Board::board_representation (){

    float value{0.f};
    unsigned int ligne {}; //i
    unsigned int colonne {}; //j
    char c_ligne {}; //chiffres
    char c_colonne {}; //lettres

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
                                ligne = i*2;
                                colonne = j*2-1;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                ImGui::PushID((ligne-1)*8 + colonne); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases);
                                ligne = i*2;
                                colonne = j*2;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                ImGui::PushID((ligne-1)*8 + colonne); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();
                            }
                            ImGui::NewLine();
                            for (int j {1}; j<5; j++){
                        
                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases);
                                ligne = i*2-1;
                                colonne = j*2-1;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                ImGui::PushID((ligne-1)*8 + colonne); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                ImGui::PushStyleColor(ImGuiCol_Button,white_cases);
                                ligne = i*2-1;
                                colonne = j*2;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                ImGui::PushID((ligne-1)*8 + colonne); 
                                if (ImGui::Button("", ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "\n";
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