#include "./includes/board.hpp"
#include <imgui.h>
#include <iostream>
#include <array>
#include <string>
#include "includes/types.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <vector>
#include "./includes/pieces.hpp"
#include "./includes/moves.hpp"

Board::Board(std::vector<Piece>& list_piece) : m_list_piece(list_piece) {};
void Board::set_fonts(ImFont* chess, ImFont* other)
{
    m_ChessFont = chess;
    m_OtherFont = other;
}
void Board::reset_piece(const std::vector<Piece>& pieces)
{
    m_list_piece = pieces;
    classic_start();
}

//test pour la représenation des square possibles
std::vector <Position> zero {};

//gestion transform pawn
bool pawn_transform_pending = false;
Position transform_position;

//board items
std::pair<Position, Position> movement {{.x=8,.y=8},{.x=8,.y=8}}; //coord start and end of a piece
std::vector<Position> list_of_possible_move = zero; 
bool selected = false;//will indicate if a square is part of a move




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

std::vector<Position> Board::positions_taken () const {
    std::vector<Position> pos_taken {};
    for (auto piece : m_list_piece){
        if (!piece.is_captured) {pos_taken.push_back(piece.current_position);}
    }
    return pos_taken;
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
    std::vector <Position> moves = piece->get_moves();
    return withdraw_collision( *piece, positions_taken(), moves);
}

bool Board::square_colored(const std::vector<Position>& squares, const Position& square) const {//verify if the square is in the list of position where the piece can be moved
    return is_in(square, squares);
}

void Board::charge_lines (){ //function making the m_lines on fonction of the pieces current position
    std::array<std::array<Piece*,8>,8> new_lines = {};
    for (Piece& piece : m_list_piece){
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
    }
    charge_lines();

    std::cout << "moved ! " <<"\n";
}


void Board::will_transform(std::pair<Position,Position>& move){// WILL make apear a pop up to change the pawn
    std::vector<Position> edges { {.x=0,.y=0}, {.x=0,.y=1}, {.x=0,.y=2}, {.x=0,.y=3}, {.x=0,.y=4}, {.x=0,.y=5}, {.x=0,.y=6}, {.x=0,.y=7},
                                {.x=7,.y=0}, {.x=7,.y=1}, {.x=7,.y=2}, {.x=7,.y=3}, {.x=7,.y=4}, {.x=7,.y=5}, {.x=7,.y=6}, {.x=7,.y=7}};
    if (m_lines[move.first.x][move.first.y]->type == piece_type::PAWN){
        if(is_in(move.second, edges)){
            std::cout<< "It's a pawn at the edge !" << '\n';
            pawn_transform_pending = true;
            transform_position = move.second;
        }
    }
}

void Board::transform(piece_type type)
{
    Piece* p = m_lines[transform_position.x][transform_position.y];
    if (p) {
        p->type = type;
    }
    pawn_transform_pending = false;
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
        will_transform(move);
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

    ImVec4 colo_case {};
    ImVec4 white_cases ={0.65f, 0.65f, 0.80f, 1.f};                  
    ImVec4 black_cases ={0.2f, 0.2f, 0.35f, 1.f};                  
    ImVec4 red_cases = {1.f, 0.f, 0.f,1.f}; //piece can be moved there

    ImVec4 colo_piece {};              
    ImVec4 white_piece ={1.f, 1.f, 1.f, 1.f};                   
    ImVec4 black_piece ={0.f, 0.f, 0.f, 1.f};       
    

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    ImGui::Begin("Board");                        
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
            ImGui::PushFont(m_ChessFont);
            square_representation(line, colum, label, colo_case, colo_piece,selected);
            ImGui::PopFont();

            //move gestion
            if (selected){
                selected = false;
                if ( movement.first.x == 8){
                    movement.first = {.x=line, .y=colum};
                    
                }
                else {movement.second = {.x=line, .y=colum};}   
            }
            

            //2
            
            line = i*2-1;
            colum = j*2-1;

            label =  get_label(line, colum);
            colo_case = (square_colored( list_of_possible_move, Position{.x=line, .y=colum}))? red_cases :black_cases; 
            colo_piece = (get_piece_color(line, colum))?white_piece :black_piece;

            ImGui::PushFont(m_ChessFont);
            square_representation(line, colum, label, colo_case, colo_piece,selected);
            ImGui::PopFont();

            if (selected){
                selected =false;
                if ( movement.first.x == 8){
                    movement.first = {.x=line, .y=colum};
                }
                else {movement.second = {.x=line, .y=colum};}
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

            ImGui::PushFont(m_ChessFont);
            square_representation(line, colum, label, colo_case, colo_piece,selected);
            ImGui::PopFont();

            if (selected){
                selected =false;
                if ( movement.first.x == 8){
                    movement.first = {.x=line, .y=colum};
                }
                else {movement.second = {.x=line, .y=colum};}
            }

            //4
            
            line = i*2-2;
            colum = j*2-1;

            label =  get_label(line,colum);
            colo_case = (square_colored( list_of_possible_move, Position{.x=line, .y=colum}))? red_cases :white_cases;
            colo_piece = (get_piece_color(line, colum))?white_piece :black_piece;

            ImGui::PushFont(m_ChessFont);
            square_representation(line, colum, label, colo_case, colo_piece,selected);
            ImGui::PopFont();

            if (selected){
                selected =false;
                if ( movement.first.x == 8){
                    movement.first = {.x=line, .y=colum};
                }
                else {movement.second = {.x=line, .y=colum};}
            }
        }
        ImGui::NewLine();
    }
    

    move_gestion(movement, list_of_possible_move);

    if (pawn_transform_pending)
    {
        ImGui::Begin("T");
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.f, 0.f));
        //ImGui::SetWindowFontScale(4.f);
        ImGui::PushStyleColor(ImGuiCol_Button, {1.f, 1.f, 1.f, 1.f});
        ImGui::PushStyleColor(ImGuiCol_Text, {1.f, 0.f, 0.f,1.f});
        //create button
        ImGui::PushID(1);
        if (ImGui::Button("Q", ImVec2{200.f, 100.f})){
                transform(piece_type::QUEEN);
                std::cout << "Wild queen appeared !" << '\n';
        }
        ImGui::PopID();
        ImGui::SameLine();
        //create button
        ImGui::PushID(2);
        if (ImGui::Button("B", ImVec2{200.f, 100.f})){
            transform(piece_type::BISHOP);
            std::cout << "Wild bishop appeared !" << '\n';
        }
        ImGui::PopID();
        ImGui::SameLine();
        //create button
        ImGui::PushID(3);
        if (ImGui::Button("N", ImVec2{200.f, 100.f})){
            transform(piece_type::KNIGHT);
            std::cout << "Wild knight appeared !" << '\n';
        }
        ImGui::PopID();
        ImGui::SameLine();
        //create button
        ImGui::PushID(4);
        if (ImGui::Button("R", ImVec2{200.f, 100.f})){
            transform(piece_type::ROOK);
            std::cout << "Wild rook appeared !" << '\n';
        }

        ImGui::PopID();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();

        ImGui::PopStyleVar();
        ImGui::End();
    }

    
    ImGui::End();
    ImGui::PopStyleVar(3);
}

void Board::classic_start (){ //function making the m_lines when beginning a classic game
    m_lines ={};
    for (Piece& piece : m_list_piece){
        m_lines[piece.initial_position.x][piece.initial_position.y] = &piece;
    }
}

// move (pion, piece de bord) -> lance la transformation ! 
// le saut du pion
