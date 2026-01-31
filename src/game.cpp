#include "./includes/game.hpp"
#include "includes/board.hpp"
#include "includes/player.hpp"

// Constructors
Game::~Game() = default;

Game::Game() : m_player(Player()), m_white_playing(true), m_board(Board()) {};
Game::Game(const Game& game) : m_player(game.m_player), m_white_playing(game.m_white_playing), m_board(game.m_board) {};

Game& Game::operator=(const Game& game)
{
    if (this != &game)
    {
        m_player        = game.m_player;
        m_white_playing = game.m_white_playing;
        m_board         = game.m_board;
    }
    return *this;
}

// Methods

void Game::start() {};
void Game::end() {};