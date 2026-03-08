#include <algorithm>
#include <iostream>
#include "./includes/board.hpp"
#include "./includes/pieces.hpp"

static void display(std::vector<Position> const& vecPos)
{
    for (Position const& pos : vecPos)
    {
        std::cout << "(x : " << pos.x << ", y : " << pos.y << "); ";
    }
}

int main()
{

    Board board{};
    board.classic_start();
    board.show_lines();
    board.board_representation();

    Piece test_pawn{
        .type                 = piece_type::PAWN,
        .is_white             = false,
        .initial_position     = {.x = 0, .y = 1},
        .current_position     = {.x = 0, .y = 1},
    };

    std::cout << "Pawn in (x :" << test_pawn.current_position.x << ", y :" << test_pawn.current_position.y << ") : \n";
    std::vector<Position> moves{test_pawn.get_moves()};
    display(moves);

    Piece test_knight{
        .type                 = piece_type::KNIGHT,
        .is_white             = true,
        .initial_position     = {.x = 0, .y = 1},
        .current_position     = {.x = 3, .y = 3},
    };

    std::cout << "\nKnight in (x :" << test_knight.current_position.x << ", y :" << test_knight.current_position.y << ") : \n";

    std::vector<Position> moves_n{test_knight.get_moves()};
    display(moves_n);

    Piece test_king{
        .type                 = piece_type::KING,
        .is_white             = true,
        .initial_position     = {.x = 0, .y = 1},
        .current_position     = {.x = 3, .y = 3},
    };

    std::cout << "\nKing in (x :" << test_king.current_position.x << ", y :" << test_king.current_position.y << ") : \n";

    std::vector<Position> moves_k{test_king.get_moves()};
    display(moves_k);

    Piece test_queen{
        .type                 = piece_type::QUEEN,
        .is_white             = true,
        .initial_position     = {.x = 0, .y = 1},
        .current_position     = {.x = 3, .y = 3},
    };

    std::cout << "\nqueen in (x :" << test_queen.current_position.x << ", y :" << test_queen.current_position.y << ") : \n";

    std::vector<Position> moves_q{test_queen.get_moves()};
    std::sort(moves_q.begin(), moves_q.end());
    display(moves_q);

    Piece test_rook{
        .type                 = piece_type::ROOK,
        .is_white             = false,
        .initial_position     = {.x = 0, .y = 1},
        .current_position     = {.x = 3, .y = 3},
    };

    std::cout << "\nrook in (x :" << test_rook.current_position.x << ", y :" << test_rook.current_position.y << ") : \n";

    std::vector<Position> moves_r{test_rook.get_moves()};
    std::sort(moves_r.begin(), moves_r.end());
    display(moves_r);

    Piece test_bishop{
        .type                 = piece_type::BISHOP,
        .is_white             = false,
        .initial_position     = {.x = 0, .y = 1},
        .current_position     = {.x = 3, .y = 3},
    };

    std::cout << "\nbishop in (x :" << test_bishop.current_position.x << ", y :" << test_bishop.current_position.y << ") : \n";

    std::vector<Position> moves_b{test_bishop.get_moves()};
    std::sort(moves_b.begin(), moves_b.end());
    display(moves_b);

    return 0;
}