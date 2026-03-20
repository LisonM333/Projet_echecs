#include "includes/moves.hpp"
#include <iostream>

// generate relative offsets for sliding pieces (bishop, rook, queen, king)
// each direction go until max steps
static std::vector<Position> generate_sliding_relative_moves(const std::vector<Position>& directions, const int max_steps)
{
    std::vector<Position> relative_moves{};
    relative_moves.reserve(static_cast<size_t>(max_steps) * directions.size());

    for (const Position& direction : directions)
    {
        for (int step{1}; step <= max_steps; step++)
        {
            relative_moves.push_back({.x = step * direction.x, .y = step * direction.y});
        }
    }
    return relative_moves;
}

// generate relative offsets for diagonal movement (bishop, queen, king)
static std::vector<Position> get_diagonal_relative_moves(const int& max_steps)
{
    const std::vector<Position> diagonal_directions{
        {.x = 1, .y = 1},
        {.x = 1, .y = -1},
        {.x = -1, .y = 1},
        {.x = -1, .y = -1},
    };

    return generate_sliding_relative_moves(diagonal_directions, max_steps);
}

// generate relative offsets for lateral movement (rook, queen, king)
static std::vector<Position> get_lateral_relative_moves(const int& max_steps)
{
    const std::vector<Position> lateral_directions{
        {.x = 1, .y = 0},
        {.x = -1, .y = 0},
        {.x = 0, .y = 1},
        {.x = 0, .y = -1},
    };

    return generate_sliding_relative_moves(lateral_directions, max_steps);
}

////////////////////
// Relative moves //
////////////////////

// convert relative moves to absolute position on the board
std::vector<Position> apply_relative_moves(const std::vector<Position>& relative_moves, const Position& position)
{
    std::vector<Position> final_moves{};
    final_moves.reserve(relative_moves.size());

    for (const Position& move : relative_moves)
    {
        final_moves.push_back({.x = position.x + move.x, .y = position.y + move.y});
    }
    return final_moves;
};

////////////////////
//      Pawn      //
////////////////////

// doesn't check if pawn on starter square
static std::vector<Position> get_pawn_forward_moves()
{
    return {{.x = 1, .y = 0}, {.x = 2, .y = 0}};
}

// doesn't check for opposite piece
static std::vector<Position> get_pawn_capture_moves()
{
    return {{.x = 1, .y = 1}, {.x = 1, .y = -1}};
}

std::vector<Position> get_pawn_relative_moves()
{
    std::vector<Position> moves{get_pawn_forward_moves()};
    std::vector<Position> capture_moves{get_pawn_capture_moves()};
    moves.insert(moves.begin(), capture_moves.begin(), capture_moves.end());

    return moves;
};

////////////////////
//     Knight     //
////////////////////

// L-shape moves
std::vector<Position> get_knight_relative_moves()
{
    std::vector<Position> positions{};
    positions.reserve(8);

    const int primary_direction{2};
    const int secondary_direction{1};

    for (int sign_x : {-1, 1})
    {
        for (int sign_y : {-1, 1})
        {
            positions.push_back({.x = sign_x * primary_direction, .y = sign_y * secondary_direction});
            positions.push_back({.x = sign_x * secondary_direction, .y = sign_y * primary_direction});
        }
    }
    return positions;
}

////////////////////
//     Bishop     //
////////////////////

std::vector<Position> get_bishop_relative_moves()
{
    return get_diagonal_relative_moves(8);
}

////////////////////
//      Rook      //
////////////////////
std::vector<Position> get_rook_relative_moves()
{
    return get_lateral_relative_moves(8);
}

////////////////////
//      King      //
////////////////////

std::vector<Position> get_king_relative_moves()
{
    std::vector<Position> relative_moves{get_lateral_relative_moves(1)};
    std::vector<Position> diagonal_moves{get_diagonal_relative_moves(1)};

    relative_moves.insert(relative_moves.begin(), diagonal_moves.begin(), diagonal_moves.end());

    return relative_moves;
}

////////////////////
//      Queen     //
////////////////////
std::vector<Position> get_queen_relative_moves()
{
    std::vector<Position> relative_moves{get_lateral_relative_moves(8)};
    std::vector<Position> diagonal_moves{get_diagonal_relative_moves(8)};

    relative_moves.insert(relative_moves.begin(), diagonal_moves.begin(), diagonal_moves.end());

    return relative_moves;
}

// all relatives moves by type
std::vector<Position> get_relative_moves(const piece_type& type)
{
    switch (type)
    {
    case piece_type::PAWN: return get_pawn_relative_moves();
    case piece_type::KNIGHT: return get_knight_relative_moves();
    case piece_type::KING: return get_king_relative_moves();
    case piece_type::QUEEN: return get_queen_relative_moves();
    case piece_type::ROOK: return get_rook_relative_moves();
    case piece_type::BISHOP: return get_bishop_relative_moves();
    default:
    {
        std::cerr << "[pieces.cpp] unknown type in get_all_relative_moves_by_type switch";
        return {};
    }
    }
};
