#include "./includes/pieces.hpp"
#include <iostream>
#include "includes/moves.hpp"
#include "includes/types.hpp"

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
    return apply_color(piece_representation(type), is_white);
}

std::vector<Position> Piece::get_moves() const
{
    std::vector<Position> relative_moves{get_relative_moves(type)};

    if (type == piece_type::PAWN && !is_white)
    {
        for (Position& pos : relative_moves)
        {
            pos.y = -pos.y;
        }
    }
    return {apply_relative_moves(relative_moves, current_position)};
}