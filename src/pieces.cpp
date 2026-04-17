#include "./includes/pieces.hpp"
#include <imgui.h>
#include <iostream>
#include "includes/moves.hpp"
#include "includes/types.hpp"

Piece::Piece(piece_type type, bool is_white, Position initial_position)
    : m_type(type), m_is_white(is_white), m_initial_position(initial_position) {};

static char piece_representation(piece_type const type)
{
    // lowercase piece symbol, color applied later
    switch (type)
    {
    case piece_type::BISHOP: return 'b';
    case piece_type::KING: return 'k';
    case piece_type::KNIGHT: return 'n';
    case piece_type::PAWN: return 'p';
    case piece_type::QUEEN: return 'q';
    case piece_type::ROOK: return 'r';
    default:
    {
        std::cerr << "[pieces.cpp] unknown type in piece_representation switch";
        return ' ';
    };
    }
};

static char apply_color(char piece_representation, bool is_white)
{
    return is_white ? static_cast<char>(toupper(piece_representation)) : static_cast<char>(tolower(piece_representation));
}

char Piece::representation() const
{
    return apply_color(piece_representation(m_type), m_is_white);
}

std::vector<Position> Piece::get_moves() const
{
    std::vector<Position> relative_moves{get_relative_moves(m_type)};

    if (m_type == piece_type::PAWN && !m_is_white)
    {
        for (Position& pos : relative_moves)
        {
            pos.x = -pos.x;
        }
    }
    return {apply_relative_moves(relative_moves, m_current_position)};
}
