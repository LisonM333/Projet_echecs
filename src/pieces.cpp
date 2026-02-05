#include "./includes/pieces.hpp"
#include <array>
#include <iostream>

// Position operator+(Position& from, const int& to)
// {
//     return {.x = from.x + to, .y = from.y + to};
// }

Position operator+(Position& from, const Position& to)
{
    return {.x = from.x + to.x, .y = from.y + to.y};
}

bool operator==(Position& pos_1, Position& pos_2)
{
    return pos_1.x == pos_2.x && pos_1.y == pos_2.y;
}

static std::vector<Position> apply_moves_to_position(const std::vector<Position>& relative_moves, const Position& position)
{
    std::vector<Position> final_moves{};
    final_moves.reserve(relative_moves.size());

    for (const Position move : relative_moves)
    {
        final_moves.push_back({.x = position.x + move.x, .y = position.y + move.y});
    }
    return final_moves;
};

static std::vector<Position> get_pawn_moves(const Position& current_position, const bool is_white)
{
    std::vector<Position> moves{};

    const int                   direction{is_white ? 1 : -1};
    const std::vector<Position> relative_moves{
        {.x = direction, .y = 0},
        {.x = direction * 2, .y = 0},
        {.x = direction, .y = direction},
        {.x = -direction, .y = direction},
    };
    return apply_moves_to_position(relative_moves, current_position);
};

std::vector<Position> get_knight_moves(const Position& current_position)
{
    std::array<int, 2> directions{-1, 1};
    const int          steps_first_direction{2};
    const int          steps_second_direction{1};

    std::vector<Position> relative_moves{};
    relative_moves.reserve(8);

    // {pos+2, pos+1} ; {pos+2, pos-1}; {pos-2, pos+1}; {pos-2, pos-1};
    // {pos+1, pos+2} ; {pos-1, pos+2}; {pos+1, pos-2}; {pos-1, pos-2};

    /*
    first*direction, second*1
    first*direction, second*-1
    */

    for (int first_direction : directions)
    {
        for (int second_direction : directions)
        {
            const Position new_position = {.x = steps_first_direction * first_direction, .y = steps_second_direction * second_direction};
            relative_moves.push_back({new_position});
        }
    }
    return apply_moves_to_position(relative_moves, current_position);
}

// std::vector<Position> get_moves(Board &board)
std::vector<Position> Piece::get_moves()
{
    switch (type)
    {
    case piece_type::PAWN: // TODO : check if it's the correct implementation cause for start it can move 2 in a row
    {
        return get_pawn_moves(current_position, is_white);
    }
    case piece_type::KNIGHT:
    {
        return get_knight_moves(current_position);
    }

    default:
        return {};
    }
    return {};
}