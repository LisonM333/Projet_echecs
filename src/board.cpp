#include "./includes/board.hpp"
#include <imgui.h>
#include <iostream>
#include <array>
#include <string>
#include "quick_imgui/quick_imgui.hpp"
#include <vector>


//test pour la représenation des square possibles
std::vector <Position> zero {};


//temporary list of position possibles
std::vector <Position> pawn_move {{.x=5,.y=0},{.x=5,.y=1},{.x=5,.y=2},{.x=5,.y=3},{.x=5,.y=4},{.x=5,.y=5},{.x=5,.y=6},{.x=5,.y=7}};
std::vector <Position> PAWN_move {{.x=2,.y=0},{.x=2,.y=1},{.x=2,.y=2},{.x=2,.y=3},{.x=2,.y=4},{.x=2,.y=5},{.x=2,.y=6},{.x=2,.y=7}};
std::vector <Position> rOoK_move {
{.x=0,.y=0},{.x=0,.y=1},{.x=0,.y=2},{.x=0,.y=3},{.x=0,.y=4},{.x=0,.y=5},{.x=0,.y=6},{.x=0,.y=7},
{.x=7,.y=1},{.x=7,.y=2},{.x=7,.y=3},{.x=7,.y=4},{.x=7,.y=5},{.x=7,.y=6},{.x=7,.y=7},
{.x=1,.y=0},{.x=2,.y=0},{.x=3,.y=0},{.x=4,.y=0},{.x=5,.y=0},{.x=6,.y=0},{.x=7,.y=0},
{.x=1,.y=7},{.x=2,.y=7},{.x=3,.y=7},{.x=4,.y=7},{.x=5,.y=7},{.x=6,.y=7}};




const char * Board::get_label(const int& line,const int& colum) const{//function translating the char in the table of pieces positions (m_lines) to a string readable by the button (to label)
    char label = this->m_lines[line][colum];
    switch (label) {
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


bool Board::get_piece_color (const char *& label) const{ //fonction giving which color the text label should be, depending of the label of a button
    std::array<std::string, 6> black {"p","r","n","b","k","q"};
    for (int i{0};i<6;i++){
        if (label == black[i]){
            return false;
        }
    }
    return true;
}//return true for white, false for black


std::vector <Position> Board::get_squares_possible(const Position& position) const{ // temporary function giving to some pieces a list of position possible
    switch (m_lines[position.x][position.y]){
        case 'P': return  PAWN_move;
        case 'R': return  rOoK_move;
        case 'p': return  pawn_move;
        case 'r': return  rOoK_move;
        default:  return  zero; //apparently this line isn't working right
    }
}


bool Board::square_colored(const std::vector<Position>& squares, const Position& square) const {//verify if the square is in the list of position where the piece can be moved
    for (const auto& s : squares){
        if (square == s){return true;}
    }
    return false;
}


void Board::show_lines ()const{ //temporary function to show the board in the terinal
    std::cout << m_lines[7][0] << "  "<< m_lines[7][1] << "  "<< m_lines[7][2] << "  "<< m_lines[7][3] << "  "<< m_lines[7][4] << "  "<< m_lines[7][5] << "  "<< m_lines[7][6] << "  "<< m_lines[7][7] << "\n";
    std::cout << m_lines[6][0] << "  "<< m_lines[6][1] << "  "<< m_lines[6][2] << "  "<< m_lines[6][3] << "  "<< m_lines[6][4] << "  "<< m_lines[6][5] << "  "<< m_lines[6][6] << "  "<< m_lines[6][7] << "\n";
    std::cout << m_lines[5][0] << "  "<< m_lines[5][1] << "  "<< m_lines[5][2] << "  "<< m_lines[5][3] << "  "<< m_lines[5][4] << "  "<< m_lines[5][5] << "  "<< m_lines[5][6] << "  "<< m_lines[5][7] << "\n";
    std::cout << m_lines[4][0] << "  "<< m_lines[4][1] << "  "<< m_lines[4][2] << "  "<< m_lines[4][3] << "  "<< m_lines[4][4] << "  "<< m_lines[4][5] << "  "<< m_lines[4][6] << "  "<< m_lines[4][7] << "\n";
    std::cout << m_lines[3][0] << "  "<< m_lines[3][1] << "  "<< m_lines[3][2] << "  "<< m_lines[3][3] << "  "<< m_lines[3][4] << "  "<< m_lines[3][5] << "  "<< m_lines[3][6] << "  "<< m_lines[3][7] << "\n";
    std::cout << m_lines[2][0] << "  "<< m_lines[2][1] << "  "<< m_lines[2][2] << "  "<< m_lines[2][3] << "  "<< m_lines[2][4] << "  "<< m_lines[2][5] << "  "<< m_lines[2][6] << "  "<< m_lines[2][7] << "\n";
    std::cout << m_lines[1][0] << "  "<< m_lines[1][1] << "  "<< m_lines[1][2] << "  "<< m_lines[1][3] << "  "<< m_lines[1][4] << "  "<< m_lines[1][5] << "  "<< m_lines[1][6] << "  "<< m_lines[1][7] << "\n";
    std::cout << m_lines[0][0] << "  "<< m_lines[0][1] << "  "<< m_lines[0][2] << "  "<< m_lines[0][3] << "  "<< m_lines[0][4] << "  "<< m_lines[0][5] << "  "<< m_lines[0][6] << "  "<< m_lines[0][7] << "\n";
}


void Board::updates_lines(const Position& start, const Position& end){//update m_lines when a piece is moved
    bool can_be_moved = square_colored(get_squares_possible(start), end);
    if (m_lines[start.x][start.y]!= ' ' && m_lines[end.x][end.y]== ' ' && can_be_moved){
        m_lines[end.x][end.y] = m_lines[start.x][start.y];
        m_lines[start.x][start.y] = ' ';
        
        std::cout << "moved ! " <<"\n";
    }
}

void Board::move_gestion(std::pair<Position, Position>& move, std::vector<Position>& list){
    //get the list of position possible after a piece was selected
    if (move.first.x != 8 && move.second.x == 8){
        list = get_squares_possible(move.first);
    }

    //avoid moving from an empty square
    if (square_is_empty(move.first)){
        move = {{.x=8,.y=8},{.x=8,.y=8}};
        list = zero;
    }

    //if the piece is selected and is final position too, m-lines is update
    if (move.first.x != 8 && move.second.x != 8){
        updates_lines(move.first, move.second);
        move = {{.x=8,.y=8},{.x=8,.y=8}};
        list = zero;
    } //a condition to have the good color or eat a piece should be added, maybe
}

void Board::square_representation (const int& line,const int& colum, const char*& label, const ImVec4& colo_case, const ImVec4& colo_piece, bool& selected) const { //responsabilise the apparence of one square
    //version in char
    char char_line = static_cast<char>(49+line);
    char char_colum = static_cast<char>(65+colum);

    // colors gestion of the button
    ImGui::PushStyleColor(ImGuiCol_Button, colo_case);
    ImGui::PushStyleColor(ImGuiCol_Text, colo_piece);

    //create button
    ImGui::PushID((line)*8 + colum + 1);
    if (ImGui::Button(label, ImVec2{100.f, 100.f})){
        //show square name in terminal
        std::cout << char_colum << char_line << "\n";
        selected = true;
    }
    ImGui::PopID();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();

    ImGui::SameLine();
}

void Board::board_representation (){ //function generating the visual of the board

    float value{0.f};
    int line {}; //i
    int colum {}; //j
    const char * label{}; //name of piece
    std::pair<Position, Position> move {{.x=8,.y=8},{.x=8,.y=8}}; //coord start and end of a piece
    std::vector<Position> list_of_possible_move = zero; 
    bool selected = false;//will indicate if a square is part of a move

    ImVec4 colo_case {};
    ImVec4 white_cases ={0.65f, 0.65f, 0.80f, 1.f};                  
    ImVec4 black_cases ={0.2f, 0.2f, 0.35f, 1.f};                  
    ImVec4 red_cases = {1.f, 0.f, 0.f,1.f}; //piece can be moved there

    ImVec4 colo_piece {};              
    ImVec4 white_piece ={1.f, 1.f, 1.f, 1.f};                   
    ImVec4 black_piece ={0.f, 0.f, 0.f, 1.f};       
    

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

                        
                        
                        for (int i {4}; i>0; i--){

                            for (int j {1}; j<5; j++){

                                //1

                                //values of line and colum
                                line = i*2-1;
                                colum = j*2-2;

                                //gestion of colors
                                label =  get_label(line,colum);
                                colo_case = (square_colored( list_of_possible_move, Position{.x=line, .y=colum}))? red_cases :white_cases;
                                colo_piece = (get_piece_color(label))?white_piece :black_piece;

                                //visual part
                                square_representation(line, colum, label, colo_case, colo_piece,selected);

                                //move gestion
                                if (selected){
                                    selected = false;
                                    if ( move.first.x == 8){
                                        move.first = {.x=line, .y=colum};
                                        
                                    }
                                    else {move.second = {.x=line, .y=colum};}   
                                }
                              

                                //2
                                
                                line = i*2-1;
                                colum = j*2-1;

                                label =  get_label(line, colum);
                                colo_case = (square_colored( list_of_possible_move, Position{.x=line, .y=colum}))? red_cases :black_cases; 
                                colo_piece = (get_piece_color(label))?white_piece :black_piece;

                                square_representation(line, colum, label, colo_case, colo_piece,selected);

                                if (selected){
                                    selected =false;
                                    if ( move.first.x == 8){
                                        move.first = {.x=line, .y=colum};
                                    }
                                    else {move.second = {.x=line, .y=colum};}
                                }
                            }

                            ImGui::NewLine();

                            for (int j {1}; j<5; j++){
                        
                                //3

                                line = i*2-2;
                                colum = j*2-2;

                                label =  get_label(line,colum);
                                colo_case = (square_colored( list_of_possible_move, Position{.x=line, .y=colum}))? red_cases :black_cases;
                                colo_piece = (get_piece_color(label))?white_piece :black_piece;

                                square_representation(line, colum, label, colo_case, colo_piece,selected);

                                if (selected){
                                    selected =false;
                                    if ( move.first.x == 8){
                                        move.first = {.x=line, .y=colum};
                                    }
                                    else {move.second = {.x=line, .y=colum};}
                                }

                                //4
                                
                                line = i*2-2;
                                colum = j*2-1;

                                label =  get_label(line,colum);
                                colo_case = (square_colored( list_of_possible_move, Position{.x=line, .y=colum}))? red_cases :white_cases;
                                colo_piece = (get_piece_color(label))?white_piece :black_piece;

                                square_representation(line, colum, label, colo_case, colo_piece,selected);

                                if (selected){
                                    selected =false;
                                    if ( move.first.x == 8){
                                        move.first = {.x=line, .y=colum};
                                    }
                                    else {move.second = {.x=line, .y=colum};}
                                }
                            }
                            ImGui::NewLine();
                        }

                        move_gestion(move, list_of_possible_move);

                        ImGui::End();
                        ImGui::PopStyleVar(3);
                    },
            }

        );

}


void Board::classic_start (){ //function making the m_lines when beginning a classic game
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

