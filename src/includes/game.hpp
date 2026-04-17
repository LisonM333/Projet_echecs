#pragma once
#include "board.hpp"
#include <imgui.h>

class Game {
private:
    // bool   m_white_playing;
    Board  m_board;
    std::vector<Piece> m_pieces;
    std::pair<Piece*, Piece*> m_kings;
    ImFont* m_Font = nullptr;

public:
    ~Game();

    Game();
    Game(const Game& game);

    Game& operator=(const Game& game);
    void  get_board();
    void  get_kings();

    void type_game(bool& classic, bool& letgo);
    bool game_ended();

    void start();
    void end();

    void show_etat();
};