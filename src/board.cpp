#include "./includes/board.hpp"
#include <imgui.h>
#include <iostream>
#include <array>
#include <string>
#include "quick_imgui/quick_imgui.hpp"



const char * Board::get_label(int line,int col) const{
    char label = this->m_lines[line][col];
    switch (label)
    {
        case 'P': return "P";
        case 'R': return  "R";
        case 'N': return  "N";
        case 'B': return  "B";
        case 'Q': return  "Q";
        case 'K': return  "K";
        case 'p': return  "p";
        case 'r': return  "r";
        case 'n': return  "n";
        case 'b': return  "b";
        case 'q': return  "q";
        case 'k': return  "k";
        default:  return  " ";
    }
}

bool piece_color (const char * label){ //return true for white, false for black
    std::array<std::string, 6> black {"p","r","n","b","k","q"};
    for (int i{0};i<6;i++){
        if (label == black[i]){
            return false;
        }
    }
    return true;
}

void Board::board_representation (){

    float value{0.f};
    unsigned int ligne {}; //i
    unsigned int colonne {}; //j
    char c_ligne {}; //chiffres
    char c_colonne {}; //lettres
    const char * label{}; //piece sur la case

        quick_imgui::loop(
            "Chess",
            {
                .init = [&]() {
                },
                .loop =
                    [&]() {
                        ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
                        ImGui::Begin("Board");
                        ImGui::SetWindowFontScale(5.f);

                        // ImVec4 white_cases ={0.85f, 0.85f, 1.f, 1.f};
                        ImVec4 white_cases ={0.65f, 0.65f, 0.80f, 1.f}; //plus sombre pour voir les labels
                        ImVec4 black_cases ={0.2f, 0.2f, 0.35f, 1.f};
                        ImVec4 white_piece ={1.f, 1.f, 1.f, 1.f}; //plus sombre pour voir les labels
                        ImVec4 black_piece ={0.f, 0.f, 0.f, 1.f};
                        ImVec4 piece_color_vec {};
                        

                        for (int i {4}; i>0; i--){

                            for (int j {1}; j<5; j++){
                                ligne = i*2;
                                colonne = j*2-1;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                label =  get_label(8-ligne,8-colonne);
                                ImGui::PushStyleColor(ImGuiCol_Button, white_cases);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "test"<< label << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                
                                ligne = i*2;
                                colonne = j*2;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                label =  get_label(8-ligne,8-colonne);
                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases); 
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();
                            }
                            ImGui::NewLine();
                            for (int j {1}; j<5; j++){
                        
                                
                                ligne = i*2-1;
                                colonne = j*2-1;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                label =  get_label(8-ligne,8-colonne);
                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne); 
                                if (ImGui::Button(label, ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                
                                ligne = i*2-1;
                                colonne = j*2;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                label =  get_label(8-ligne,8-colonne);
                                ImGui::PushStyleColor(ImGuiCol_Button,white_cases);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{200.f, 200.f}))
                                    std::cout << c_colonne << c_ligne << "\n";
                                ImGui::PopID();
                                ImGui::PopStyleColor();
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

void Board::classic_start (){ //par la suite ce code ira chercher les positions initiales de chaque pièce
    this->m_lines = {{
        {{'r','n','b','q','k','b','n','r'}},
        {{'p','p','p','p','p','p','p','p'}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{'P','P','P','P','P','P','P','P'}},
        {{'R','N','B','Q','K','B','N','R'}}
    }};
}