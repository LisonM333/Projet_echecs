#include "./includes/board.hpp"
#include "./includes/pieces.hpp"

int main()
{
    Board board;
    board.classic_start();
    board.board_representation();

    Piece test_piece{
        .type = piece_type::PAWN,
        .is_white             = true,
        .piece_representation = 'p',
        .initial_position     = {.x = 0, .y = 1},
        .current_position     = {.x = 0, .y = 1},
    };
    
    std::vector<Position> moves {test_piece.get_moves()};
    return 0;
}