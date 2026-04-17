#include "./includes/game.hpp"
#include "includes/board.hpp"
#include "includes/pieces.hpp"
#include <iostream>
#include <vector>
#include <imgui.h>
#include "quick_imgui/quick_imgui.hpp"

//other
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
std::vector<Piece> list_pieces_classic {Pw_1, Pw_2,Pw_3, Pw_4,Pw_5, Pw_6,Pw_7, Pw_8,
                            Pb_1, Pb_2,Pb_3, Pb_4, Pb_5, Pb_6, Pb_7, Pb_8,
                            Rw_1, Rw_2,Nw_1, Nw_2,Bw_1, Bw_2,Qw, Kw,
                            Rb_1, Rb_2,Nb_1, Nb_2, Bb_1, Bb_2, Qb, Kb};



// Constructors
Game::~Game() = default;

Game::Game() :  /*m_white_playing(true),*/ m_board(Board(list_pieces_classic)), m_pieces(list_pieces_classic) {};
Game::Game(const Game& game) :  /*m_white_playing(game.m_white_playing),*/ m_board(game.m_board), m_pieces(game.m_pieces) {};

Game& Game::operator=(const Game& game)
{
    if (this != &game)
    {
        /*m_white_playing = game.m_white_playing;*/
        m_board         = game.m_board;
        m_pieces        = game.m_pieces;
    }
    return *this;
}

// Methods
void Game::get_kings(){
    m_kings = m_board.get_kings();
}

bool Game::game_ended(){return m_kings.first->is_captured || m_kings.second->is_captured;}

void Game::type_game(bool& classic, bool& letgo){
    ImGui::PushFont(m_Font);
    //ImGui::ShowDemoWindow();
    ImGui::Begin("Game");

    ImGui::PushID(1);
    if (ImGui::Button("Classic", ImVec2{250.f, 100.f})){
            std::cout << "Let's go for classic !" << '\n';
            classic = true;
            letgo = true;
    }
    ImGui::PopID();

    ImGui::PushID(2);
    if (ImGui::Button("Chaotic", ImVec2{250.f, 100.f})){
            std::cout << "Let's go for chaotic !" << '\n';
            classic = false;
            letgo = true;
    }
    ImGui::PopID();
    ImGui::End();
    ImGui::PopFont();
}

void Game::end() {
    ImGui::PushFont(m_Font);
    ImGui::Begin("END");
    if (m_kings.first->is_captured) {
        ImGui::Text("Félicitations aux Noirs ! Ils ont gagné !");
    } else if (m_kings.second->is_captured) {
        ImGui::Text("Félicitations aux Blancs ! Ils ont gagné !");
    }
    ImGui::End();
    ImGui::PopFont();
}

void Game::show_etat(){
    for (Piece piece : m_pieces){
        std::cout << piece.is_captured; 
    }
    std::cout << std::endl;
}

void Game::start() {
    bool classic = true;
    bool letgo = false;
    bool initialized = false;
    bool game_over = false;

    quick_imgui::loop(
        "Chess",
        {
            .init = [&]() {
                ImGuiIO& io = ImGui::GetIO();

                ImFont* chess = io.Fonts->AddFontFromFileTTF(
                 "C:\\Users\\ADMIN\\Desktop\\imac_2\\Prog_Objet_2\\projet\\Projet_echecs\\assets\\font\\chess_font\\Chessfont-Regular.ttf", 90.0f);

                ImFont* other = io.Fonts->AddFontFromFileTTF(
                "C:\\Users\\ADMIN\\Desktop\\imac_2\\Prog_Objet_2\\projet\\Projet_echecs\\assets\\font\\Nunito\\static\\Nunito-Regular.ttf", 90.0f);

                set_fonts(m_board, chess, other);
                m_Font = other;
            },

            .loop = [&]() {
                if (!letgo) {
                type_game(classic, letgo);
                }

                if (letgo && classic) {
                    if (!initialized) {
                        m_board.reset_piece(list_pieces_classic);
                        m_pieces = list_pieces_classic;
                        get_kings();
                        initialized = true;
                        
                    }

                    m_board.board_representation();

                    //show_etat();
                    //m_board.show_etat();

                        if (!game_over && game_ended()){
                            game_over = true;
                            std::cout << "fin du game !" <<'\n';
                        }

                        if (game_over){
                            end();
                        }
                }
            },
        }
    );
};


