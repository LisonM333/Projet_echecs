// #include <iostream>

#include <iostream>
#include "./includes/board.hpp"
#include "./includes/maths.hpp"
// #include "./includes/pieces.hpp"

int main()
{
    Board board{};
    board.classic_start();
    // board.show_lines();
    // board.board_representation();
    // board.board_representation();

    // Piece pawn{};
    // std::cout << "pawn : " << pawn.representation() << ',' << (pawn.is_white ? "white" : "black")
    //           << "\ninitial position : x ->" << pawn.initial_position.x << ", y ->" << pawn.initial_position.y
    //           << "\ncurrent position : x ->" << pawn.current_position.x << ", y ->" << pawn.current_position.y;

    double lambda{0.2f};
    double probability_of_one{0.1f};
    // std::vector<double> generated{use_exponential_law(300, lambda)};
    // std::vector<double> generated{use_bernoulli_law( 300, probability_of_one)};
    // std::vector <double> generated{use_binomial_law(300, 10, probability_of_one)};
    std::vector<double> generated{use_geometrical_law(300, probability_of_one)};
    // std::string         visualize_str{bernoulli_vizualisation(generated)};
    std::string         visualize_str{visualization(generated)};

    std::cout << "\n Generated : " << generated[0] << ", " << generated[1] << ", " << generated[2];
    std::cout << "\n";
    std::cout << visualize_str << "\n";
    return 0;
}