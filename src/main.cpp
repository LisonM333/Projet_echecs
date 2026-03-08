#include "./includes/board.hpp"
#include "./includes/pieces.hpp"

int main()
{
    Board board;
    board.classic_start();
    board.show_lines();
    board.board_representation();

    return 0;
}