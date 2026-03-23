#include "./includes/board.hpp"
#include <imgui.h>
#include <iostream>
#include <array>
#include <string>
#include "quick_imgui/quick_imgui.hpp"
#include <vector>
#include "./includes/pieces.hpp"


//test pour la représenation des square possibles
std::vector <Position> zero {};




//temporary instancations of the pieces
Piece Pw_1 (piece_type::PAWN, true, false, {.x=1, .y=0},{.x=1, .y=0});
Piece Pw_2 (piece_type::PAWN, true, false, {.x=1, .y=1},{.x=1, .y=1});
Piece Pw_3 (piece_type::PAWN, true, false, {.x=1, .y=2},{.x=1, .y=2});
Piece Pw_4 (piece_type::PAWN, true, false, {.x=1, .y=3},{.x=1, .y=3});
Piece Pw_5 (piece_type::PAWN, true, false, {.x=1, .y=4},{.x=1, .y=4});
Piece Pw_6 (piece_type::PAWN, true, false, {.x=1, .y=5},{.x=1, .y=5});
Piece Pw_7 (piece_type::PAWN, true, false, {.x=1, .y=6},{.x=1, .y=6});
Piece Pw_8 (piece_type::PAWN, true, false, {.x=1, .y=7},{.x=1, .y=7});
Piece Pb_1 (piece_type::PAWN, false, false, {.x=6, .y=0},{.x=6, .y=0});
Piece Pb_2 (piece_type::PAWN, false, false, {.x=6, .y=1},{.x=6, .y=1});
Piece Pb_3 (piece_type::PAWN, false, false, {.x=6, .y=2},{.x=6, .y=2});
Piece Pb_4 (piece_type::PAWN, false, false, {.x=6, .y=3},{.x=6, .y=3});
Piece Pb_5 (piece_type::PAWN, false, false, {.x=6, .y=4},{.x=6, .y=4});
Piece Pb_6 (piece_type::PAWN, false, false, {.x=6, .y=5},{.x=6, .y=5});
Piece Pb_7 (piece_type::PAWN, false, false, {.x=6, .y=6},{.x=6, .y=6});
Piece Pb_8 (piece_type::PAWN, false, false, {.x=6, .y=7},{.x=6, .y=7});
Piece Rw_1 (piece_type::ROOK, true, false, {.x=0, .y=0},{.x=0, .y=0});
Piece Rw_2 (piece_type::ROOK, true, false, {.x=0, .y=7},{.x=0, .y=7});
Piece Nw_1 (piece_type::KNIGHT, true, false, {.x=0, .y=1},{.x=0, .y=1});
Piece Nw_2 (piece_type::KNIGHT, true, false, {.x=0, .y=6},{.x=0, .y=6});
Piece Bw_1 (piece_type::BISHOP, true, false, {.x=0, .y=2},{.x=0, .y=2});
Piece Bw_2 (piece_type::BISHOP, true, false, {.x=0, .y=5},{.x=0, .y=5});
Piece Qw (piece_type::QUEEN, true, false, {.x=0, .y=3},{.x=0, .y=3});
Piece Kw (piece_type::KING, true, false, {.x=0, .y=4},{.x=0, .y=4});
Piece Rb_1 (piece_type::ROOK, false, false, {.x=7, .y=0},{.x=7, .y=0});
Piece Rb_2 (piece_type::ROOK, false, false, {.x=7, .y=7},{.x=7, .y=7});
Piece Nb_1 (piece_type::KNIGHT, false, false, {.x=7, .y=1},{.x=7, .y=1});
Piece Nb_2 (piece_type::KNIGHT, false, false, {.x=7, .y=6},{.x=7, .y=6});
Piece Bb_1 (piece_type::BISHOP, false, false, {.x=7, .y=2},{.x=7, .y=2});
Piece Bb_2 (piece_type::BISHOP, false, false, {.x=7, .y=5},{.x=7, .y=5});
Piece Qb (piece_type::QUEEN, false, false, {.x=7, .y=3},{.x=7, .y=3});
Piece Kb (piece_type::KING, false, false, {.x=7, .y=4},{.x=7, .y=4});
std::vector<Piece> list_pieces {Pw_1, Pw_2,Pw_3, Pw_4,Pw_5, Pw_6,Pw_7, Pw_8,
                            Pb_1, Pb_2,Pb_3, Pb_4, Pb_5, Pb_6, Pb_7, Pb_8,
                            Rw_1, Rw_2,Nw_1, Nw_2,Bw_1, Bw_2,Qw, Kw,
                            Rb_1, Rb_2,Nb_1, Nb_2, Bb_1, Bb_2, Qb, Kb};







template <typename T, typename Q>
bool Board::is_in (const T& value, const std::vector<Q>& list) const{ //function retruning true if a value is in a list
    size_t size {list.size()};
    for (int i{0};i<size;i++){
        if constexpr (std::is_same_v<T, Piece>){
            if (operateur_egal_piece(list[i],value)){return true;}}
        else{if (value == list[i]){return true;}}
    }
    return false;
}

std::optional<piece_type> Board::get_type(const int& line, const int& colum) const { //function giving the type of a piece
    Piece* piece = m_lines[line][colum];

    if (!piece) {
        return std::nullopt;  // there's no piece
    }

    return piece->type;       // retrun the piece's type
}

const char * Board::get_label(const int& line,const int& colum) const{//function translating the char in the table of pieces positions (m_lines) to a string readable by the button (to label)
    Piece* piece = m_lines[line][colum];

    if (!piece || piece->is_captured) {return " ";}

    char c {};
    switch (piece->type) {
        case piece_type::PAWN:   c = 'P'; break;
        case piece_type::ROOK:   c = 'R'; break;
        case piece_type::KNIGHT: c = 'N'; break;
        case piece_type::BISHOP: c = 'B'; break;
        case piece_type::QUEEN:  c = 'Q'; break;
        case piece_type::KING:   c = 'K'; break;
        default:                 c = '?'; break;
    }

    if (!piece->is_white) {
        c = static_cast<char>(std::tolower(c));
    }

    static char buf[2]; // buffer temporaire pour ImGui
    buf[0] = c;
    buf[1] = '\0';
    return buf;
}

bool Board::get_piece_color (const int& line,const int& colum) const{ //fonction giving which color the text label should be, depending of the label of a button
    Piece* piece = m_lines[line][colum];
    return piece ? piece->is_white : true;
}//return true for white, false for black

std::vector <Position> Board::get_squares_possible(const Position& position) const{ // temporary function giving to some pieces a list of position possible
    Piece* piece = m_lines[position.x][position.y];
    if (!piece) return zero; // return zero
    return piece->get_moves();
}

bool Board::square_colored(const std::vector<Position>& squares, const Position& square) const {//verify if the square is in the list of position where the piece can be moved
    return is_in(square, squares);
}

// void Board::show_lines ()const{ //temporary function to show the board in the terinal
//     std::cout << m_lines[7][0] << "  "<< m_lines[7][1] << "  "<< m_lines[7][2] << "  "<< m_lines[7][3] << "  "<< m_lines[7][4] << "  "<< m_lines[7][5] << "  "<< m_lines[7][6] << "  "<< m_lines[7][7] << "\n";
//     std::cout << m_lines[6][0] << "  "<< m_lines[6][1] << "  "<< m_lines[6][2] << "  "<< m_lines[6][3] << "  "<< m_lines[6][4] << "  "<< m_lines[6][5] << "  "<< m_lines[6][6] << "  "<< m_lines[6][7] << "\n";
//     std::cout << m_lines[5][0] << "  "<< m_lines[5][1] << "  "<< m_lines[5][2] << "  "<< m_lines[5][3] << "  "<< m_lines[5][4] << "  "<< m_lines[5][5] << "  "<< m_lines[5][6] << "  "<< m_lines[5][7] << "\n";
//     std::cout << m_lines[4][0] << "  "<< m_lines[4][1] << "  "<< m_lines[4][2] << "  "<< m_lines[4][3] << "  "<< m_lines[4][4] << "  "<< m_lines[4][5] << "  "<< m_lines[4][6] << "  "<< m_lines[4][7] << "\n";
//     std::cout << m_lines[3][0] << "  "<< m_lines[3][1] << "  "<< m_lines[3][2] << "  "<< m_lines[3][3] << "  "<< m_lines[3][4] << "  "<< m_lines[3][5] << "  "<< m_lines[3][6] << "  "<< m_lines[3][7] << "\n";
//     std::cout << m_lines[2][0] << "  "<< m_lines[2][1] << "  "<< m_lines[2][2] << "  "<< m_lines[2][3] << "  "<< m_lines[2][4] << "  "<< m_lines[2][5] << "  "<< m_lines[2][6] << "  "<< m_lines[2][7] << "\n";
//     std::cout << m_lines[1][0] << "  "<< m_lines[1][1] << "  "<< m_lines[1][2] << "  "<< m_lines[1][3] << "  "<< m_lines[1][4] << "  "<< m_lines[1][5] << "  "<< m_lines[1][6] << "  "<< m_lines[1][7] << "\n";
//     std::cout << m_lines[0][0] << "  "<< m_lines[0][1] << "  "<< m_lines[0][2] << "  "<< m_lines[0][3] << "  "<< m_lines[0][4] << "  "<< m_lines[0][5] << "  "<< m_lines[0][6] << "  "<< m_lines[0][7] << "\n";
// }

void Board::charge_lines (){ //function making the m_lines on fonction of the pieces current position
    std::array<std::array<Piece*,8>,8> new_lines = {};
    for (Piece& piece : list_pieces){
        if (piece.is_captured) continue;
            new_lines[piece.current_position.x][piece.current_position.y] = &piece;
    }
    m_lines = new_lines;
}

void Board::updates_lines(const Position& start, const Position& end){//update m_lines when a piece is moved
    bool can_be_moved = square_colored(get_squares_possible(start), end);
    if (m_lines[start.x][start.y] != nullptr && can_be_moved){
        if (m_lines[end.x][end.y] != nullptr) {
            if (m_lines[end.x][end.y]->is_white == m_lines[start.x][start.y]->is_white){return;}
                    
                m_lines[end.x][end.y]->is_captured=true;
        }
        m_lines[start.x][start.y]->current_position=end;
        //m_lines[end.x][end.y] = m_lines[start.x][start.y];
        //m_lines[start.x][start.y] = nullptr;
    }
    charge_lines();

    std::cout << "moved ! " <<"\n";
}


void Board::transform_pawn(std::pair<Position,Position>& move){// WILL make apear a pop up to change the pawn
    std::vector<Position> edges { {.x=0,.y=0}, {.x=0,.y=1}, {.x=0,.y=2}, {.x=0,.y=3}, {.x=0,.y=4}, {.x=0,.y=5}, {.x=0,.y=6}, {.x=0,.y=7},
                                {.x=7,.y=0}, {.x=7,.y=1}, {.x=7,.y=2}, {.x=7,.y=3}, {.x=7,.y=4}, {.x=7,.y=5}, {.x=7,.y=6}, {.x=7,.y=7}};
    if (m_lines[move.first.x][move.first.y]->type == piece_type::PAWN){
        if(is_in(move.second, edges)){
            std::cout<< "It's a pawn at the edge !" << '\n';
        }
    }
}

void Board::move_gestion(std::pair<Position, Position>& move, std::vector<Position>& list){//gestion of the moves in general
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
        transform_pawn(move);
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
                                colo_piece = (get_piece_color(line, colum))?white_piece :black_piece;

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
                                colo_piece = (get_piece_color(line, colum))?white_piece :black_piece;

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
                                colo_piece = (get_piece_color(line, colum))?white_piece :black_piece;

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
                                colo_piece = (get_piece_color(line, colum))?white_piece :black_piece;

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
    m_lines ={};
    for (Piece& piece : list_pieces){
        m_lines[piece.initial_position.x][piece.initial_position.y] = &piece;
    }
}

