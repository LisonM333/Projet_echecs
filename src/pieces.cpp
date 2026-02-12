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
        {.x = 0, .y = direction},
        {.x = 0, .y = direction * 2},
        {.x = direction, .y = direction},
        {.x = -direction, .y = direction},
    };
    return apply_moves_to_position(relative_moves, current_position);
};

static std::vector<Position> get_positions_with_fixed_x_y_steps(const Steps& steps)
{
    std::vector<Position> fixed_positions{};
    fixed_positions.reserve(8);

    std::array<int, 2> directions{-1, 1};
    for (int first_direction : directions)
    {
        for (int second_direction : directions)
        {
            const int x = steps.first_direction * first_direction;
            const int y = steps.second_direction * second_direction;

            fixed_positions.push_back({.x = x, .y = y});
            fixed_positions.push_back({.x = y, .y = x});
        }
    }
    return {fixed_positions};
}

static std::vector<Position> get_knight_moves(const Position& current_position)
{
    std::vector<Position> relative_moves{};
    relative_moves.reserve(8);

    relative_moves = {get_positions_with_fixed_x_y_steps({.first_direction = 2, .second_direction = 1})};

    // {pos+2, pos+1} ; {pos+2, pos-1}; {pos-2, pos+1}; {pos-2, pos-1};
    // {pos+1, pos+2} ; {pos-1, pos+2}; {pos+1, pos-2}; {pos-1, pos-2};

    /*
    first*direction, second*1
    first*direction, second*-1
    */

    return apply_moves_to_position(relative_moves, current_position);
}

// TODO(later) : apply positions is on all of moves maybe get relatives moves and all apply in the same place

static std::vector<Position> get_diagonal_moves(const int& max_steps)
{
    std::vector<Position> moves{};
    std::array<int, 2>    directions{-1, 1};

    for (int first_direction : directions)
    {
        for (int second_direction : directions)
        {
            for (int step{1}; step <= max_steps; step++)
            {
                moves.push_back({.x = step * first_direction, .y = step * second_direction});
            }
        }
    }
    return {moves};
}

static std::vector<Position> get_lateral_moves(const int& max_steps)
{
    std::vector<Position> moves{};
    std::array<int, 2>    directions{-1, 1};

    for (int first_direction : directions)
    {
        for (int step{1}; step <= max_steps; step++)
        {
            moves.push_back({.x = step * first_direction, .y = 0});
            moves.push_back({.x = 0, .y = step * first_direction});
        }
    }
    return {moves};
}

static std::vector<Position> get_king_moves(const Position& current_position)
{
    std::vector<Position> relative_moves{};
    relative_moves.reserve(8);

    std::vector<Position> lateral_moves  = {get_lateral_moves(1)};
    std::vector<Position> diagonal_moves = {get_diagonal_moves(1)};

    relative_moves.insert(relative_moves.begin(), lateral_moves.begin(), lateral_moves.end());
    relative_moves.insert(relative_moves.begin(), diagonal_moves.begin(), diagonal_moves.end());

    return apply_moves_to_position(relative_moves, current_position);
};

static std::vector<Position> get_queen_moves(const Position& current_position)
{
    std::vector<Position> relative_moves{};
    relative_moves.reserve(56);

    std::vector<Position> lateral_moves  = {get_lateral_moves(8)};
    std::vector<Position> diagonal_moves = {get_diagonal_moves(8)};

    relative_moves.insert(relative_moves.begin(), lateral_moves.begin(), lateral_moves.end());
    relative_moves.insert(relative_moves.begin(), diagonal_moves.begin(), diagonal_moves.end());

    return apply_moves_to_position(relative_moves, current_position);
}

// std::vector<Position> get_moves(Board &board)
std::vector<Position> Piece::get_moves() const
{
    switch (type)
    {
    case piece_type::PAWN: // TODO(check) : check if it's the correct implementation cause for start it can move 2 in a row
    {
        return get_pawn_moves(current_position, is_white);
    }
    case piece_type::KNIGHT:
    {
        return get_knight_moves(current_position);
    }

    case piece_type::KING:
    {
        return get_king_moves(current_position);
    }

    case piece_type::QUEEN:
    {
        return get_queen_moves(current_position);
    }

    default:
        std::cerr << "[pieces.cpp] default case in switch Pieces::get_moves()";
        return {};
    }
    return {};
}