#include "includes/moves.hpp"
#include <iostream>
#include "includes/pieces.hpp"
#include "includes/types.hpp"

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


std::vector<Position> withdraw_collision_lateral(const Piece& moved,
const std::vector<Position>& board,
const std::vector<Position>& relative_moves_applied){
    std::vector<Position> new_moves = relative_moves_applied;
    Position position = moved.current_position;
    std::pair<bool,int> dir_up = {false, 9};
    std::pair<bool,int> dir_down = {false, -1};
    std::pair<bool,int> dir_right = {false, 9};
    std::pair<bool,int> dir_left = {false, -1};
    for (Position piece : board){
        if (piece.x<position.x && piece.y == position.y){
            dir_down.first = true;
            dir_down.second = std::max(dir_down.second, piece.x);
        }
        if (piece.x>position.x && piece.y == position.y){
            dir_up.first = true;
            dir_up.second = std::min(dir_up.second, piece.x);
        }
        if (piece.x == position.x && piece.y<position.y){
            dir_left.first = true;
            dir_left.second = std::max(dir_left.second, piece.y);
        }
        if (piece.x == position.x && piece.y>position.y){
            dir_right.first = true;
            dir_right.second = std::min(dir_right.second, piece.y);
        }
    }
    for (Position moves : relative_moves_applied){
        if (dir_down.first && moves.x<dir_down.second && moves.y==position.y){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
        if (dir_up.first && moves.x>dir_up.second && moves.y==position.y){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
        if (dir_left.first && moves.x==position.x && moves.y<dir_left.second){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
        if (dir_right.first && moves.x==position.x && moves.y>dir_right.second){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
    }
    return new_moves;
}

std::vector<Position> withdraw_collision_diagonal(const Piece& moved,
                                        const std::vector<Position>& board,
                                        const std::vector<Position>& relative_moves_applied){
    std::vector<Position> new_moves = relative_moves_applied;
    Position position = moved.current_position;
    std::pair<bool,Position> dir_up_right = {false, {9,9}};
    std::pair<bool,Position> dir_up_left = {false, {9,-1}};
    std::pair<bool,Position> dir_down_right= {false, {-1, 9}};
    std::pair<bool,Position> dir_down_left = {false, {-1,-1}};
    for (Position piece : board){
        if (piece.x-piece.y == position.x-position.y && piece.x > position.x){
            dir_up_right.first = true;
            dir_up_right.second = (dir_up_right.second.x < piece.x) ? dir_up_right.second : piece;
        }
        if (piece.x-piece.y == position.x-position.y && piece.x < position.x){
            dir_down_left.first = true;
            dir_down_left.second = (dir_down_left.second.x > piece.x) ? dir_down_left.second : piece;
        }
        if (piece.x+piece.y == position.x+position.y && piece.x > position.x){
            dir_up_left.first = true;
            dir_up_left.second = (dir_up_left.second.x < piece.x) ? dir_up_left.second : piece;
        }
        if (piece.x+piece.y == position.x+position.y && piece.x < position.x){
            dir_down_right.first = true;
            dir_down_right.second = (dir_down_right.second.x > piece.x) ? dir_down_right.second : piece;
        }
    }
    for (Position moves : relative_moves_applied){
        if (dir_up_right.first && moves.x>dir_up_right.second.x && moves.x-moves.y==position.x-position.y){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
        if (dir_down_left.first && moves.x<dir_down_left.second.x && moves.x-moves.y==position.x-position.y){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
        if (dir_up_left.first && moves.x+moves.y==position.x+position.y && moves.x>dir_up_left.second.x){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
        if (dir_down_right.first && moves.x+moves.y==position.x+position.y && moves.x<dir_down_right.second.x){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);
        }
    }
    return new_moves;
}

std::vector<Position> withdraw_collision_pawn(const Piece&  moved,
                                        const std::vector<Position>& board, //list of position taken on the board by pieces
                                        //const Position& position, //position of the piece moving, on the board
                                        const std::vector<Position>& relative_moves_applied ) //list of movement possible
{
    std::vector<Position> new_moves = relative_moves_applied;
    Position position = moved.current_position;
    bool dir_left = true;
    bool dir_right = true;
    bool dir_updown = false;
    bool dir_upupdowndown = false;
    int signe = (moved.is_white) ? 1 : -1;
    bool initial_pos = (moved.initial_position == moved.current_position);
    for (Position piece : board){
        if (piece.x == position.x+signe && piece.y == position.y-1){
            dir_left = false;
        }
        if (piece.x == position.x+signe && piece.y == position.y+1){
            dir_right = false;
        }
        if (piece.x == position.x+signe && piece.y == position.y){
            dir_updown = true;
        }
        if (initial_pos && piece.x == position.x+2*signe && piece.y == position.y){
            dir_upupdowndown = true;
        }
    }
    for(Position moves : relative_moves_applied){
        if (dir_left && moves.x == position.x+signe && moves.y == position.y-1){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
            
        if (dir_right && moves.x == position.x+signe && moves.y == position.y+1){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }

        if (dir_updown && moves.x == position.x+signe && moves.y == position.y){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }

        if ((!initial_pos || dir_updown || dir_upupdowndown) && moves.x == position.x+2*signe){
            auto it = std::find(new_moves.begin(), new_moves.end(), moves);
            if (it != new_moves.end())
                new_moves.erase(it);            }
    }
    return new_moves;
}
    

std::vector<Position> withdraw_collision(const Piece&  moved,
                                        const std::vector<Position>& board, //list of position taken on the board by pieces
                                        //const Position& position, //position of the piece moving, on the board
                                        const std::vector<Position>& relative_moves_applied ) //list of movement possible
{
    std::vector<Position> new_moves = relative_moves_applied;
    Position position = moved.current_position;
    if (moved.type ==piece_type::ROOK || moved.type == piece_type::QUEEN){
        new_moves = withdraw_collision_lateral(moved, board, relative_moves_applied);
    }

    if (moved.type ==piece_type::BISHOP || moved.type == piece_type::QUEEN){
        new_moves = withdraw_collision_diagonal(moved, board, relative_moves_applied);
    }

    if (moved.type == piece_type::PAWN){
        new_moves = withdraw_collision_pawn(moved, board, relative_moves_applied);
    }

    return new_moves;
}

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
