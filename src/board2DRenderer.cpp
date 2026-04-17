// #include "board2DRenderer.hpp"
// #include <cctype>
// #include <iostream>

// const char* get_label(const Board& board, const int& line, const int& colum)
// { // function translating the char in the table of pieces positions (m_lines) to a string readable by the button (to label)
//     Piece* piece = board.get_lines()[line][colum];

//     if (!piece || piece->m_is_captured)
//     {
//         return " ";
//     }

//     char c{};
//     switch (piece->m_type)
//     {
//     case piece_type::PAWN: c = 'P'; break;
//     case piece_type::ROOK: c = 'R'; break;
//     case piece_type::KNIGHT: c = 'N'; break;
//     case piece_type::BISHOP: c = 'B'; break;
//     case piece_type::QUEEN: c = 'Q'; break;
//     case piece_type::KING: c = 'K'; break;
//     default: c = '?'; break;
//     }

//     if (!piece->m_is_white)
//     {
//         c = static_cast<char>(std::tolower(c));
//     }

//     static char buf[2]; // buffer temporaire pour ImGui
//     buf[0] = c;
//     buf[1] = '\0';
//     return buf;
// }

// bool square_colored(const std::vector<Position>& squares, const Position& square)
// {
//     return is_in(square, squares);
// }

// void square_representation(const int& line, const int& colum, const char*& label, const ImVec4& colo_case, const ImVec4& colo_piece, bool& selected)
// { // responsabilise the apparence of one square
//     // version in char
//     char char_line  = static_cast<char>(49 + line);
//     char char_colum = static_cast<char>(65 + colum);

//     // colors gestion of the button
//     ImGui::PushStyleColor(ImGuiCol_Button, colo_case);
//     ImGui::PushStyleColor(ImGuiCol_Text, colo_piece);

//     // create button
//     ImGui::PushID((line) * 8 + colum + 1);
//     if (ImGui::Button(label, ImVec2{100.f, 100.f}))
//     {
//         // show square name in terminal
//         std::cout << char_colum << char_line << "\n";
//         selected = true;
//     }
//     ImGui::PopID();
//     ImGui::PopStyleColor();
//     ImGui::PopStyleColor();

//     ImGui::SameLine();
// }

// // TODO: remove global variables and replace with proper ones
// // bad and old code due to board importation
// std::pair<Position, Position> movement{{.x = 8, .y = 8}, {.x = 8, .y = 8}}; // coord start and end of a piece
// std::vector<Position>         zero{};
// std::vector<Position>         list_of_possible_move = zero;
// bool                          selected              = false; // will indicate if a square is part of a move

// // visualize 2D Board
// void board2DRendererImGui(Board const& board)
// { // function generating the visual of the board

//     float       value{0.f};
//     int         line{};  // i
//     int         colum{}; // j
//     const char* label{}; // name of piece

//     ImVec4 colo_case{};
//     ImVec4 white_cases = {0.65f, 0.65f, 0.80f, 1.f};
//     ImVec4 black_cases = {0.2f, 0.2f, 0.35f, 1.f};
//     ImVec4 red_cases   = {1.f, 0.f, 0.f, 1.f}; // piece can be moved there

//     ImVec4 colo_piece{};
//     ImVec4 white_piece = {1.f, 1.f, 1.f, 1.f};
//     ImVec4 black_piece = {0.f, 0.f, 0.f, 1.f};

//     ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
//     ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
//     ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
//     ImGui::Begin("Board");
//     for (int i{4}; i > 0; i--)
//     {
//         for (int j{1}; j < 5; j++)
//         {
//             // 1

//             // values of line and colum
//             line  = i * 2 - 1;
//             colum = j * 2 - 2;

//             // gestion of colors
//             label      = get_label(board, line, colum);
//             colo_case  = (square_colored(list_of_possible_move, Position{.x = line, .y = colum})) ? red_cases : white_cases;
//             colo_piece = (board.get_piece_color(line, colum)) ? white_piece : black_piece;

//             // visual part
//             ImGui::PushFont(board.getChessFont());
//             square_representation(line, colum, label, colo_case, colo_piece, selected);
//             ImGui::PopFont();

//             // move gestion
//             if (selected)
//             {
//                 selected = false;
//                 if (movement.first.x == 8)
//                 {
//                     movement.first = {.x = line, .y = colum};
//                 }
//                 else
//                 {
//                     movement.second = {.x = line, .y = colum};
//                 }
//             }

//             // 2

//             line  = i * 2 - 1;
//             colum = j * 2 - 1;

//             label      = get_label(line, colum);
//             colo_case  = (square_colored(list_of_possible_move, Position{.x = line, .y = colum})) ? red_cases : black_cases;
//             colo_piece = (board.get_piece_color(line, colum)) ? white_piece : black_piece;

//             ImGui::PushFont(board.getChessFont());
//             square_representation(line, colum, label, colo_case, colo_piece, selected);
//             ImGui::PopFont();

//             if (selected)
//             {
//                 selected = false;
//                 if (movement.first.x == 8)
//                 {
//                     movement.first = {.x = line, .y = colum};
//                 }
//                 else
//                 {
//                     movement.second = {.x = line, .y = colum};
//                 }
//             }
//         }

//         ImGui::NewLine();

//         for (int j{1}; j < 5; j++)
//         {
//             // 3

//             line  = i * 2 - 2;
//             colum = j * 2 - 2;

//             label      = get_label(line, colum);
//             colo_case  = (square_colored(list_of_possible_move, Position{.x = line, .y = colum})) ? red_cases : black_cases;
//             colo_piece = (board.get_piece_color(line, colum)) ? white_piece : black_piece;

//             ImGui::PushFont(board.getChessFont());
//             square_representation(line, colum, label, colo_case, colo_piece, selected);
//             ImGui::PopFont();

//             if (selected)
//             {
//                 selected = false;
//                 if (movement.first.x == 8)
//                 {
//                     movement.first = {.x = line, .y = colum};
//                 }
//                 else
//                 {
//                     movement.second = {.x = line, .y = colum};
//                 }
//             }

//             // 4

//             line  = i * 2 - 2;
//             colum = j * 2 - 1;

//             label      = get_label(line, colum);
//             colo_case  = (square_colored(list_of_possible_move, Position{.x = line, .y = colum})) ? red_cases : white_cases;
//             colo_piece = (board.get_piece_color(line, colum)) ? white_piece : black_piece;

//             ImGui::PushFont(board.getChessFont());
//             square_representation(line, colum, label, colo_case, colo_piece, selected);
//             ImGui::PopFont();

//             if (selected)
//             {
//                 selected = false;
//                 if (movement.first.x == 8)
//                 {
//                     movement.first = {.x = line, .y = colum};
//                 }
//                 else
//                 {
//                     movement.second = {.x = line, .y = colum};
//                 }
//             }
//         }
//         ImGui::NewLine();
//     }

//     move_gestion(movement, list_of_possible_move);

//     if (pawn_transform_pending)
//     {
//         ImGui::Begin("T");
//         ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.f, 0.f));
//         // ImGui::SetWindowFontScale(4.f);
//         ImGui::PushStyleColor(ImGuiCol_Button, {1.f, 1.f, 1.f, 1.f});
//         ImGui::PushStyleColor(ImGuiCol_Text, {1.f, 0.f, 0.f, 1.f});
//         // create button
//         ImGui::PushID(1);
//         if (ImGui::Button("Q", ImVec2{200.f, 100.f}))
//         {
//             transform(piece_type::QUEEN);
//             std::cout << "Wild queen appeared !" << '\n';
//         }
//         ImGui::PopID();
//         ImGui::SameLine();
//         // create button
//         ImGui::PushID(2);
//         if (ImGui::Button("B", ImVec2{200.f, 100.f}))
//         {
//             transform(piece_type::BISHOP);
//             std::cout << "Wild bishop appeared !" << '\n';
//         }
//         ImGui::PopID();
//         ImGui::SameLine();
//         // create button
//         ImGui::PushID(3);
//         if (ImGui::Button("N", ImVec2{200.f, 100.f}))
//         {
//             transform(piece_type::KNIGHT);
//             std::cout << "Wild knight appeared !" << '\n';
//         }
//         ImGui::PopID();
//         ImGui::SameLine();
//         // create button
//         ImGui::PushID(4);
//         if (ImGui::Button("R", ImVec2{200.f, 100.f}))
//         {
//             transform(piece_type::ROOK);
//             std::cout << "Wild rook appeared !" << '\n';
//         }

//         ImGui::PopID();
//         ImGui::PopStyleColor();
//         ImGui::PopStyleColor();

//         ImGui::PopStyleVar();
//         ImGui::End();
//     }

//     ImGui::End();
//     ImGui::PopStyleVar(3);
// }
