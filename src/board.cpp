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
//fonction translating the char in the table of pieces placement (m_lines) to a string readable by the button (to label)

bool piece_color (const char * label){ //return true for white, false for black
    std::array<std::string, 6> black {"p","r","n","b","k","q"};
    for (int i{0};i<6;i++){
        if (label == black[i]){
            return false;
        }
    }
    return true;
}
//fonction giving whcich color the policie should be depending of the label of a button

void Board::show_lines (){ //temporary function to verify the upadte_line
    std::cout << m_lines[7][0] << "  "<< m_lines[7][1] << "  "<< m_lines[7][2] << "  "<< m_lines[7][3] << "  "<< m_lines[7][4] << "  "<< m_lines[7][5] << "  "<< m_lines[7][6] << "  "<< m_lines[7][7] << "\n";
    std::cout << m_lines[6][0] << "  "<< m_lines[6][1] << "  "<< m_lines[6][2] << "  "<< m_lines[6][3] << "  "<< m_lines[6][4] << "  "<< m_lines[6][5] << "  "<< m_lines[6][6] << "  "<< m_lines[6][7] << "\n";
    std::cout << m_lines[5][0] << "  "<< m_lines[5][1] << "  "<< m_lines[5][2] << "  "<< m_lines[5][3] << "  "<< m_lines[5][4] << "  "<< m_lines[5][5] << "  "<< m_lines[5][6] << "  "<< m_lines[5][7] << "\n";
    std::cout << m_lines[4][0] << "  "<< m_lines[4][1] << "  "<< m_lines[4][2] << "  "<< m_lines[4][3] << "  "<< m_lines[4][4] << "  "<< m_lines[4][5] << "  "<< m_lines[4][6] << "  "<< m_lines[4][7] << "\n";
    std::cout << m_lines[3][0] << "  "<< m_lines[3][1] << "  "<< m_lines[3][2] << "  "<< m_lines[3][3] << "  "<< m_lines[3][4] << "  "<< m_lines[3][5] << "  "<< m_lines[3][6] << "  "<< m_lines[3][7] << "\n";
    std::cout << m_lines[2][0] << "  "<< m_lines[2][1] << "  "<< m_lines[2][2] << "  "<< m_lines[2][3] << "  "<< m_lines[2][4] << "  "<< m_lines[2][5] << "  "<< m_lines[2][6] << "  "<< m_lines[2][7] << "\n";
    std::cout << m_lines[1][0] << "  "<< m_lines[1][1] << "  "<< m_lines[1][2] << "  "<< m_lines[1][3] << "  "<< m_lines[1][4] << "  "<< m_lines[1][5] << "  "<< m_lines[1][6] << "  "<< m_lines[1][7] << "\n";
    std::cout << m_lines[0][0] << "  "<< m_lines[0][1] << "  "<< m_lines[0][2] << "  "<< m_lines[0][3] << "  "<< m_lines[0][4] << "  "<< m_lines[0][5] << "  "<< m_lines[0][6] << "  "<< m_lines[0][7] << "\n";
}

void Board::updates_lines(std::pair<int, int> start, std::pair<int,int> end){
    bool can_be_moved = true;

    if (m_lines[start.first][start.second]!= ' ' && m_lines[end.first][end.second]== ' ' && can_be_moved){
        m_lines[end.first][end.second] = m_lines[start.first][start.second];
        m_lines[start.first][start.second] = ' ';
        std::cout << "moved !" <<"\n";
    }

    //show_lines();
}

void Board::board_representation (){

    float value{0.f};
    unsigned int ligne {}; //i
    unsigned int colonne {}; //j
    char c_ligne {}; //number
    char c_colonne {}; //lettres
    const char * label{}; //name of piece
    std::pair<std::pair<int,int>, std::pair<int,int>> moved {{8,8},{8,8}}; //coord start and end of a piece

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

                        ImVec4 white_cases ={0.65f, 0.65f, 0.80f, 1.f};
                        ImVec4 black_cases ={0.2f, 0.2f, 0.35f, 1.f};
                        ImVec4 white_piece ={1.f, 1.f, 1.f, 1.f};
                        ImVec4 black_piece ={0.f, 0.f, 0.f, 1.f};
                        ImVec4 piece_color_vec {};
                        
                        for (int i {4}; i>0; i--){

                            for (int j {1}; j<5; j++){
                                ligne = i*2;
                                colonne = j*2-1;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                label =  get_label(ligne-1,colonne-1);
                                ImGui::PushStyleColor(ImGuiCol_Button, white_cases);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.first == 8){
                                        moved.first = {ligne-1, colonne-1};
                                    }
                                    else {moved.second = {ligne-1, colonne-1};}
                                }
                                ImGui::PopID();
                                ImGui::PopStyleColor();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                
                                ligne = i*2;
                                colonne = j*2;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                label =  get_label(ligne-1,colonne-1);
                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases); 
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.first == 8){
                                        moved.first = {ligne-1, colonne-1};
                                    }
                                    else {moved.second = {ligne-1, colonne-1};}
                                }
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
                                label =  get_label(ligne-1,colonne-1);
                                ImGui::PushStyleColor(ImGuiCol_Button, black_cases);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne); 
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.first == 8){
                                        moved.first = {ligne-1, colonne-1};
                                    }
                                    else {moved.second = {ligne-1, colonne-1};}
                                }
                                ImGui::PopID();
                                ImGui::PopStyleColor();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();

                                
                                ligne = i*2-1;
                                colonne = j*2;
                                c_ligne = static_cast<char>(48+ligne);
                                c_colonne = static_cast<char>(64+colonne);
                                label =  get_label(ligne-1,colonne-1);
                                ImGui::PushStyleColor(ImGuiCol_Button,white_cases);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.first == 8){
                                        moved.first = {ligne-1, colonne-1};
                                    }
                                    else {moved.second = {ligne-1, colonne-1};}
                                }
                                ImGui::PopID();
                                ImGui::PopStyleColor();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();
                            }
                            ImGui::NewLine();
                        }

                        
                        
                        if (moved.first.first != 8 && moved.second.first != 8){
                            updates_lines(moved.first, moved.second);
                            moved = {{8,8},{8,8}};
                        }

                        ImGui::End();
                        ImGui::PopStyleVar(3);
                    },
            }

        );

}
//fonction making the visual of the board

void Board::classic_start (){ //par la suite ce code ira chercher les positions initiales de chaque pièce
    this->m_lines = {{
        {{'R','N','B','Q','K','B','N','R'}},
        {{'P','P','P','P','P','P','P','P'}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{' ',' ',' ',' ',' ',' ',' ',' '}},
        {{'p','p','p','p','p','p','p','p'}},
        {{'r','n','b','q','k','b','n','r'}}
    }};
}
//fonction making the m_lines like the beginning of a game

