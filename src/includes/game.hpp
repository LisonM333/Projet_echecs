#pragma once
#include "board.hpp"
#include "player.hpp"
#include <imgui.h>

class Game {
private:
    Player m_player;
    bool   m_white_playing;
    Board  m_board;
    std::vector<Piece> m_pieces;

public:
    ~Game();

    Game();
    Game(const Game& game);

    Game& operator=(const Game& game);
    void  get_board();

    void type_game(bool& classic, bool& letgo);

    void start();
    void end();
};