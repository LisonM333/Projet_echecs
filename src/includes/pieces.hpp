#pragma once

#include <cstdint>
#include <vector>

enum class piece_type : uint8_t {
    PAWN,
    KNIGHT,
    KING,
    QUEEN,
    ROOK,
    BISHOP,
};

// temporary
struct Position {
    int x; // number
    int y; // letter
};

struct Steps {
    int first_direction;
    int second_direction;
};

struct Piece {
    piece_type            type;
    bool                  is_white;
    char                  piece_representation;
    Position              initial_position;
    Position              current_position;
    std::vector<Position> get_moves() const;
};

Position operator+(Position& from, const int& to);
Position operator+(Position& from, const Position& to);
bool     operator==(Position& pos_1, Position& pos_2);

std::vector<Position> move(Piece& piece, Position& position);