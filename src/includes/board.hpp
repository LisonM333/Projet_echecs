#pragma once
#include <imgui.h>
#include <array>
#include <vector>
#include <optional>
#include "./includes/pieces.hpp"
#include "./includes/moves.hpp"



class Board {

    private :
    std::array<std::array<Piece*,8>,8> m_lines = {};
    std::vector<Piece> m_list_piece = {};

    public:
    ImFont* m_ChessFont = nullptr;
    ImFont* m_OtherFont = nullptr;

    Board(std::vector<Piece>& list_piece);
    void set_fonts(ImFont* chess, ImFont* other);
    void reset_piece(const std::vector<Piece>& pieces);

    //void show_lines() const;
    void charge_lines ();

    void square_representation(const int& line, const int& colum, const char*& label, const ImVec4& colo_case, const ImVec4& colo_piece, bool& selected) const;
    void board_representation();
    void classic_start();
    void move_gestion(std::pair<Position, Position>& move, std::vector<Position>& list);

    std::optional<piece_type> get_type(const int& line, const int& colum) const;
    const char * get_label(const int& line,const int& colum) const;
    bool square_colored(const std::vector<Position>& squares,const Position& square) const;
    bool get_piece_color (const int& line,const int& colum) const;
    bool square_is_empty(const Position& square) const {if (square.x != 8){return (m_lines[square.x][square.y]== nullptr);} else {return false;}};
    template <typename T, typename Q>
    bool is_in(const T& value, const std::vector<Q>& list) const; // T and Q are different only for the case of the comparaison between char* and string
    std::vector<Position> positions_taken ()const;

    std::vector<Position> get_squares_possible(const Position& position) const;
    void                  updates_lines(const Position& start, const Position& end);

    void will_transform(std::pair<Position, Position>& move);
    void transform(piece_type type);
};

inline bool operateur_egal_pos(const Position& a, const Position& b){return (a.x==b.x && a.y==b.y);};
inline bool operateur_egal_piece(const Piece& a, const Piece& b){return operateur_egal_pos(a.initial_position, b.initial_position);};