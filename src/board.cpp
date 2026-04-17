// #include "board.hpp"
// #include <iostream>

// /* Constructors */
// Board::Board() = default;
// Board::Board(const std::vector<Piece>& list_pieces) : m_list_pieces(list_pieces) {};

// /* Fonts */
// void Board::setFonts(ImFont* chess, ImFont* other)
// {
//     m_ChessFont = chess;
//     m_OtherFont = other;
// }

// /* Piece */
// void Board::reset_piece(const std::vector<Piece>& pieces)
// {
//     m_list_pieces = pieces;
//     classic_start();
// }

// bool Board::get_piece_color(const int& line, const int& colum) const
// { // fonction giving which color the text label should be, depending of the label of a button
//     Piece* piece = m_lines[line][colum];
//     return piece ? piece->m_is_white : true;
// } // return true for white, false for black

// /*Start*/
// void Board::classic_start()
// { // function making the m_lines when beginning a classic game
//     m_lines = {};
//     for (Piece& piece : m_list_pieces)
//     {
//         m_lines[piece.m_initial_position.x][piece.m_initial_position.y] = &piece;
//     }
// }

// /*Concerning board directly*/
// std::array<std::array<Piece*, 8>, 8> Board::get_lines() const
// {
//     return m_lines;
// }

// template<typename T, typename Q>
// bool is_in(const T& value, const std::vector<Q>& list) // T and Q are different only for the case of the comparaison between char* and string
// {
//     size_t size{list.size()};
//     for (int i{0}; i < size; i++)
//     {
//         if constexpr (std::is_same_v<T, Piece>)
//         {
//             if (operateur_egal_piece(list[i], value))
//             {
//                 return true;
//             }
//         }
//         else
//         {
//             if (value == list[i])
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// // TODO: remove this (due to board importation)
// std::vector<Position> zero{};
// // gestion transform pawn
// bool     pawn_transform_pending = false;
// Position transform_position;

// void will_transform(const Board& board, std::pair<Position, Position>& move)
// { // WILL make apear a pop up to change the pawn
//     std::vector<Position> edges{{.x = 0, .y = 0}, {.x = 0, .y = 1}, {.x = 0, .y = 2}, {.x = 0, .y = 3}, {.x = 0, .y = 4}, {.x = 0, .y = 5}, {.x = 0, .y = 6}, {.x = 0, .y = 7}, {.x = 7, .y = 0}, {.x = 7, .y = 1}, {.x = 7, .y = 2}, {.x = 7, .y = 3}, {.x = 7, .y = 4}, {.x = 7, .y = 5}, {.x = 7, .y = 6}, {.x = 7, .y = 7}};
//     if (board.get_lines()[move.first.x][move.first.y]->type == piece_type::PAWN)
//     {
//         if (is_in(move.second, edges))
//         {
//             std::cout << "It's a pawn at the edge !" << '\n';
//             pawn_transform_pending = true;
//             transform_position     = move.second;
//         }
//     }
// }

// void move_gestion(const Board& board, std::pair<Position, Position>& move, std::vector<Position>& list)
// { // gestion of the moves in general
//     // get the list of position possible after a piece was selected
//     if (move.first.x != 8 && move.second.x == 8)
//     {
//         list = board.get_squares_possible(move.first);
//     }

//     // avoid moving from an empty square
//     if (board.square_is_empty(move.first))
//     {
//         move = {{.x = 8, .y = 8}, {.x = 8, .y = 8}};
//         list = zero;
//     }

//     // if the piece is selected and is final position too, m-lines is update
//     if (move.first.x != 8 && move.second.x != 8)
//     {
//         will_transform(move);
//         updates_lines(move.first, move.second);
//         move = {{.x = 8, .y = 8}, {.x = 8, .y = 8}};
//         list = zero;
//     } // a condition to have the good color or eat a piece should be added, maybe
// }