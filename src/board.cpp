#include "./includes/board.hpp"
#include <imgui.h>
#include <ios>
#include <iostream>
#include <array>
#include <string>
#include "quick_imgui/quick_imgui.hpp"
#include <vector>
#include <random>



//test pour la représenation des square possibles
std::vector <Position> zero {};
std::vector <Position> one {{.x=8,.y=8},{.x=0,.y=1},{.x=7,.y=4},{.x=1,.y=3},{.x=4,.y=0}};
std::vector <Position> two {{.x=1,.y=1},{.x=2,.y=2},{.x=4,.y=4},{.x=5,.y=5},};
std::vector <Position> three {{.x=0,.y=0},{.x=0,.y=7},{.x=7,.y=0}};

std::vector <Position> pawn_move {{.x=5,.y=0},{.x=5,.y=1},{.x=5,.y=2},{.x=5,.y=3},{.x=5,.y=4},{.x=5,.y=5},{.x=5,.y=6},{.x=5,.y=7}};
std::vector <Position> PAWN_move {{.x=2,.y=0},{.x=2,.y=1},{.x=2,.y=2},{.x=2,.y=3},{.x=2,.y=4},{.x=2,.y=5},{.x=2,.y=6},{.x=2,.y=7}};
std::vector <Position> rOoK_move {
{.x=0,.y=0},{.x=0,.y=1},{.x=0,.y=2},{.x=0,.y=3},{.x=0,.y=4},{.x=0,.y=5},{.x=0,.y=6},{.x=0,.y=7},
{.x=7,.y=1},{.x=7,.y=2},{.x=7,.y=3},{.x=7,.y=4},{.x=7,.y=5},{.x=7,.y=6},{.x=7,.y=7},
{.x=1,.y=0},{.x=2,.y=0},{.x=3,.y=0},{.x=4,.y=0},{.x=5,.y=0},{.x=6,.y=0},{.x=7,.y=0},
{.x=1,.y=7},{.x=2,.y=7},{.x=3,.y=7},{.x=4,.y=7},{.x=5,.y=7},{.x=6,.y=7}};











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
}//fonction translating the char in the table of pieces placement (m_lines) to a string readable by the button (to label)


bool piece_color (const char * label){ //return true for white, false for black
    std::array<std::string, 6> black {"p","r","n","b","k","q"};
    for (int i{0};i<6;i++){
        if (label == black[i]){
            return false;
        }
    }
    return true;
}//fonction giving whcich color the policie should be depending of the label of a button


std::vector <Position> Board::get_squares_possible(Position test){ //chatgpt coded
    switch (m_lines[test.x][test.y])
    {
        case 'P': return  PAWN_move;
        case 'R': return  rOoK_move;
        case 'p': return  pawn_move;
        case 'r': return  rOoK_move;
        default:  return  three;
    }
} //temporary fonction to teste


bool Board::square_colored(std::vector <Position> squares, Position square){
    for (const auto& s : squares)
        if (square == s)
            return true;

    return false;
}//verify if the square is in the squares xhere the piece can be moved


void Board::show_lines (){ //temporary function to verify the upadte_line
    std::cout << m_lines[7][0] << "  "<< m_lines[7][1] << "  "<< m_lines[7][2] << "  "<< m_lines[7][3] << "  "<< m_lines[7][4] << "  "<< m_lines[7][5] << "  "<< m_lines[7][6] << "  "<< m_lines[7][7] << "\n";
    std::cout << m_lines[6][0] << "  "<< m_lines[6][1] << "  "<< m_lines[6][2] << "  "<< m_lines[6][3] << "  "<< m_lines[6][4] << "  "<< m_lines[6][5] << "  "<< m_lines[6][6] << "  "<< m_lines[6][7] << "\n";
    std::cout << m_lines[5][0] << "  "<< m_lines[5][1] << "  "<< m_lines[5][2] << "  "<< m_lines[5][3] << "  "<< m_lines[5][4] << "  "<< m_lines[5][5] << "  "<< m_lines[5][6] << "  "<< m_lines[5][7] << "\n";
    std::cout << m_lines[4][0] << "  "<< m_lines[4][1] << "  "<< m_lines[4][2] << "  "<< m_lines[4][3] << "  "<< m_lines[4][4] << "  "<< m_lines[4][5] << "  "<< m_lines[4][6] << "  "<< m_lines[4][7] << "\n";
    std::cout << m_lines[3][0] << "  "<< m_lines[3][1] << "  "<< m_lines[3][2] << "  "<< m_lines[3][3] << "  "<< m_lines[3][4] << "  "<< m_lines[3][5] << "  "<< m_lines[3][6] << "  "<< m_lines[3][7] << "\n";
    std::cout << m_lines[2][0] << "  "<< m_lines[2][1] << "  "<< m_lines[2][2] << "  "<< m_lines[2][3] << "  "<< m_lines[2][4] << "  "<< m_lines[2][5] << "  "<< m_lines[2][6] << "  "<< m_lines[2][7] << "\n";
    std::cout << m_lines[1][0] << "  "<< m_lines[1][1] << "  "<< m_lines[1][2] << "  "<< m_lines[1][3] << "  "<< m_lines[1][4] << "  "<< m_lines[1][5] << "  "<< m_lines[1][6] << "  "<< m_lines[1][7] << "\n";
    std::cout << m_lines[0][0] << "  "<< m_lines[0][1] << "  "<< m_lines[0][2] << "  "<< m_lines[0][3] << "  "<< m_lines[0][4] << "  "<< m_lines[0][5] << "  "<< m_lines[0][6] << "  "<< m_lines[0][7] << "\n";
}//show in the terminal the board (useful to verify thing) 
//will be erased before the final render


void Board::updates_lines(Position start, Position end){
    bool can_be_moved = square_colored(get_squares_possible(start), end);
    
    if (m_lines[start.x][start.y]!= ' ' && m_lines[end.x][end.y]== ' ' && can_be_moved){
        m_lines[end.x][end.y] = m_lines[start.x][start.y];
        m_lines[start.x][start.y] = ' ';
        
        std::cout << "moved ! " <<std::boolalpha<< can_be_moved <<"\n";
    }
    else {std::cout << "not moved ! " <<std::boolalpha<< can_be_moved <<"\n";}
    
    //show_lines();
}//update m_lines when a piece is moved


void Board::board_representation (){

    float value{0.f};
    int ligne {}; //i
    int colonne {}; //j
    char c_ligne {}; //number
    char c_colonne {}; //lettres
    const char * label{}; //name of piece
    std::pair<Position, Position> moved {{.x=8,.y=8},{.x=8,.y=8}}; //coord start and end of a piece
    std::vector<Position> list_of_possible_move = zero;
    ImVec4 colo_case {};

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
                        ImVec4 red_cases = {1.f, 0.f, 0.f,1.f}; //piece can be moved there
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
                                colo_case = (square_colored( list_of_possible_move, Position{.x=ligne-1, .y=colonne-1}))? red_cases :white_cases;
                                ImGui::PushStyleColor(ImGuiCol_Button, colo_case);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.x == 8){
                                        moved.first = {.x=ligne-1, .y=colonne-1};
                                    }
                                    else {moved.second = {.x=ligne-1, .y=colonne-1};}
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
                                colo_case = (square_colored( list_of_possible_move, Position{.x=ligne-1, .y=colonne-1}))? red_cases :black_cases;
                                ImGui::PushStyleColor(ImGuiCol_Button, colo_case); 
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.x == 8){
                                        moved.first = {.x=ligne-1, .y=colonne-1};
                                    }
                                    else {moved.second = {.x=ligne-1, .y=colonne-1};}
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
                                colo_case = (square_colored( list_of_possible_move, Position{.x=ligne-1, .y=colonne-1}))? red_cases :black_cases;
                                ImGui::PushStyleColor(ImGuiCol_Button, colo_case);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne); 
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.x == 8){
                                        moved.first = {.x=ligne-1, .y=colonne-1};
                                    }
                                    else {moved.second = {.x=ligne-1, .y=colonne-1};}
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
                                colo_case = (square_colored( list_of_possible_move, Position{.x=ligne-1, .y=colonne-1}))? red_cases :white_cases;
                                ImGui::PushStyleColor(ImGuiCol_Button, colo_case);
                                piece_color_vec = (piece_color(label))?white_piece :black_piece;
                                ImGui::PushStyleColor(ImGuiCol_Text, piece_color_vec);
                                ImGui::PushID((ligne-1)*8 + colonne);
                                if (ImGui::Button(label, ImVec2{100.f, 100.f})){
                                    std::cout << c_colonne << c_ligne << "\n";
                                    if (moved.first.x == 8){
                                        moved.first = {.x=ligne-1, .y=colonne-1};
                                    }
                                    else {moved.second = {.x=ligne-1, .y=colonne-1};}
                                }
                                ImGui::PopID();
                                ImGui::PopStyleColor();
                                ImGui::PopStyleColor();

                                ImGui::SameLine();
                            }
                            ImGui::NewLine();
                        }

                        if (moved.first.x != 8 && moved.second.x == 8){
                            list_of_possible_move = get_squares_possible(moved.first);
                        }

                        if (square_is_empty(moved.first)){
                            moved = {{.x=8,.y=8},{.x=8,.y=8}};
                            list_of_possible_move = zero;
                            std::cout << "zut" << "\n";
                        }

                        if (moved.first.x != 8 && moved.second.x != 8){
                            updates_lines(moved.first, moved.second);
                            moved = {{.x=8,.y=8},{.x=8,.y=8}};
                            list_of_possible_move = zero;
                        }


                        ImGui::End();
                        ImGui::PopStyleVar(3);
                    },
            }

        );

}//fonction making the visual of the board


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
}//fonction making the m_lines like the beginning of a game

