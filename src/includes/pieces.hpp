#pragma once
#include <imgui.h>
#include <glm/glm.hpp>
#include <vector>
#include "types.hpp"

struct Position {
    int x; // number
    int y; // letter

    bool operator==(const Position& B) const { return ((x == B.x) && (y == B.y)); };

    bool operator<(const Position& B) const
    {
        if (x < B.x)
            return true;
        if (x > B.x)
            return false;
        return y < B.y;
    }
};

struct Piece {
    piece_type            m_type{};
    bool                  m_is_white{};
    bool                  m_is_captured{false};
    Position              m_initial_position{};
    Position              m_current_position{m_initial_position};
    std::vector<Position> get_moves() const;

    char representation() const;

    Piece(piece_type type, bool is_white, Position initial_position);
};

std::vector<Position> move(Piece& piece, Position& position);