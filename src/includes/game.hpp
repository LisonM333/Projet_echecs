#pragma once
#include "board.hpp"
#include "player.hpp"

class Game {
private:
    Player m_player;
    bool   m_white_playing;
    Board  m_board;

public:
    ~Game();

    Game();
    Game(const Game& game);

    Game& operator=(const Game& game);
    void  get_board();

    void start();
    void end();
};