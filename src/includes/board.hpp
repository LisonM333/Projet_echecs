// #pragma once
// #include <array>
// #include <vector>
// #include "pieces.hpp"

// class Board {
// public:
//     /* Constructors */
//     Board();
//     explicit Board(std::vector<Piece> const& list_pieces);

//     /*Concerning board directly*/
//     // void board_representation();
//     std::array<std::array<Piece*, 8>, 8> get_lines() const;

//     /*Fonts*/
//     ImFont* getChessFont() const { return m_ChessFont; };
//     ImFont* getOtherFont() const { return m_OtherFont; };
//     void    setFonts(ImFont* chess, ImFont* other);

//     /* Pieces */
//     void                  reset_piece(const std::vector<Piece>& pieces);
//     bool                  get_piece_color(const int& line, const int& colum) const;
//     std::vector<Position> get_squares_possible(const Position& position) const;
//     bool square_is_empty(const Position& square) const {if (square.x != 8){return (m_lines[square.x][square.y]== nullptr);} else {return false;}};
   

//     /* Start */
//     void classic_start();

// private:
//     std::array<std::array<Piece*, 8>, 8> m_lines{};
//     std::vector<Piece>                   m_list_pieces{};
//     ImFont*                              m_ChessFont = nullptr;
//     ImFont*                              m_OtherFont = nullptr;
// };

// template<typename T, typename Q>
// bool is_in(const T& value, const std::vector<Q>& list);

// void move_gestion(const Board& board, std::pair<Position, Position>& move, std::vector<Position>& list);
// void will_transform(const Board& board, std::pair<Position, Position>& move);