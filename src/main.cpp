// #include <glad/glad.h>
// #include <glimac/FilePath.hpp>
// #include <glimac/FreeflyCamera.hpp>
#include <glad/glad.h>
#include <imgui.h>
#include <array>
#include <cstddef>
#include <exception>
#include <glimac/FilePath.hpp>
#include <vector>
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "glimac/TrackballCamera.hpp"
#include "glimac/common.hpp"
#include "glm/fwd.hpp"
#include "includes/types.hpp"
#include "quick_imgui/quick_imgui.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glimac/Geometry.hpp>
#include <glimac/Sphere.hpp>
#include <iostream>
#include <map>
#include "pieces.hpp"

const unsigned int screen_width{800};
const unsigned int screen_height{800};

// std::vector<Piece> init_m_pieces (){

static std::vector<piece_type> list_different_pieces_types()
{
    return {piece_type::PAWN, piece_type::BISHOP, piece_type::KING, piece_type::KNIGHT, piece_type::QUEEN, piece_type::ROOK};
    // std::vector<Piece> different_pieces {piece_type::PAWN};
    // Piece white_piece{piece_type::PAWN, true, {1, static_cast<float>(i)}};
}

// static std::vector<Mesh> init_3D_meshes_pieces(std::vector<Piece> const& pieces, glimac::FilePath& appPath)
// static std::vector<Mesh> init_3D_meshes_pieces(std::vector<piece_type> const& pieces_types, glimac::FilePath& appPath)
// {
//     std::vector<Mesh> meshes{};
//     // std::vector<glimac::Geometry> meshes{};
//     meshes.reserve(pieces_types.size());

//     // for (const Piece& piece_type : pieces_types)
//     for (const piece_type& type : pieces_types)
//     {
//         glimac::Geometry obj_white{};
//         glimac::Geometry obj_black{};

//         glimac::FilePath filepath{appPath.dirPath() + "/assets/models"};
//         bool             success{true};

//         switch (type)
//         {
//         case piece_type::PAWN:
//             success = obj_white.loadOBJ(filepath + "/Pawn/Pawn_white.obj", filepath + "/Pawn/Pawn_white.mtl");
//             obj_black.loadOBJ(filepath + "/Pawn/Pawn_black.obj", filepath + "/Pawn/Pawn_black.mtl");

//             std::cout << "path : " << filepath + "/Pawn/Pawn_white.obj";

//             // obj_white.loadOBJ(filepath + "/Untitled.obj", filepath + "/Untitled.mtl");
//             break;

//         case piece_type::BISHOP:
//             obj_white.loadOBJ(filepath + "/Bishop/Bishop_white.obj", filepath + "/Bishop/Bishop_white.mtl");
//             obj_black.loadOBJ(filepath + "/Bishop/Bishop_black.obj", filepath + "/Bishop/Bishop_black.mtl");
//             break;

//         case piece_type::KING:
//             obj_white.loadOBJ(filepath + "/King/King_white.obj", filepath + "/King/King_white.mtl");
//             obj_black.loadOBJ(filepath + "/King/King_black.obj", filepath + "/King/King_black.mtl");
//             break;

//         case piece_type::KNIGHT:
//             obj_white.loadOBJ(filepath + "/Knight/Knight_white.obj", filepath + "/Knight/Knight_white.mtl", true);
//             obj_black.loadOBJ(filepath + "/Knight/Knight_black.obj", filepath + "/Knight/Knight_black.mtl", true);
//             break;

//         case piece_type::QUEEN:
//             obj_white.loadOBJ(filepath + "/Queen/Queen_white.obj", filepath + "/Queen/Queen_white.mtl", true);
//             obj_black.loadOBJ(filepath + "/Queen/Queen_black.obj", filepath + "/Queen/Queen_black.mtl", true);
//             break;

//         case piece_type::ROOK:
//             obj_white.loadOBJ(filepath + "/Rook/Rook_white.obj", filepath + "/Rook/Rook_white.mtl", true);
//             obj_black.loadOBJ(filepath + "/Rook/Rook_black.obj", filepath + "/Rook/Rook_black.mtl", true);
//             break;
//         }

//         if (!success)
//         {
//             std::cout << "BBBBBBBBBBBB";
//         }
//         Mesh mesh_white{obj_white};
//         Mesh mesh_black{obj_black};

//         meshes.push_back(std::move(mesh_white));
//         meshes.push_back(std::move(mesh_black));

//         // meshes.push_back(std::move(obj_white));
//         // meshes.push_back(std::move(obj_black));
//     }
//     return meshes;
// }

// struct TransformMatrices {
//     glm::mat4 ProjMatrix;
//     glm::mat4 MVMatrix;
//     glm::mat4 NormalMatrix;
// };

// void draw_meshes()

// new type for linking piece_type + is_white and Mesh
using MeshMap = std::map<std::pair<piece_type, bool>, Mesh>;

static MeshMap init_3D_meshes_pieces(std::vector<piece_type> const& types, glimac::FilePath& appPath)
{
    MeshMap          meshes;
    glimac::FilePath modelsPath = appPath.dirPath() + "/assets/models";

    for (const auto& type : types)
    {
        glimac::Geometry obj_white;
        glimac::Geometry obj_black;
        std::string      folder;

        switch (type)
        {
        case piece_type::PAWN: folder = "/Pawn/Pawn"; break;
        case piece_type::BISHOP: folder = "/Bishop/Bishop"; break;
        case piece_type::KING: folder = "/King/King"; break;
        case piece_type::KNIGHT: folder = "/Knight/Knight"; break;
        case piece_type::QUEEN: folder = "/Queen/Queen"; break;
        case piece_type::ROOK: folder = "/Rook/Rook"; break;
        }

        std::string whitePathObj = modelsPath.str() + folder + "_white.obj";
        std::string blackPathObj = modelsPath.str() + folder + "_black.obj";

        std::string whitePathMtl = modelsPath.str() + folder + "_white.mtl";
        std::string blackPathMtl = modelsPath.str() + folder + "_black.mtl";

        obj_white.loadOBJ(whitePathObj, whitePathMtl);
        obj_black.loadOBJ(blackPathObj, blackPathMtl);

        meshes.emplace(std::make_pair(type, true), Mesh(obj_white));
        meshes.emplace(std::make_pair(type, false), Mesh(obj_black));
    }
    return meshes;
}

void renderEverything(char** argv, std::array<std::array<Piece*, 8>, 8> lines)
{
    // FreeflyCamera    camera{};
    TrackballCamera  camera{};
    glimac::FilePath appPath(argv[0]);

    std::optional<Renderer> renderer;
    std::optional<Shader>   shader;
    std::optional<Mesh>     boardMesh;
    // glimac::Geometry cube;

    // std::vector<Piece>      pieces{init_game_2D_m_pieces()};
    std::vector<piece_type> pieces_type{list_different_pieces_types()};

    MeshMap meshes;
    // std::vector<glimac::Geometry> meshes;

    ShaderFile shader_files{.vertexFile = "/assets/shaders/3D.vs.glsl", .fragmentFile = "/assets/shaders/normals.fs.glsl"};

    quick_imgui::loop(
        "Chessimac",
        {.init = [&]() {
            renderer.emplace(screen_width, screen_height);
            try
            {
                shader.emplace(appPath, shader_files);
            }
            catch (const std::exception&)
            {
                std::cout << "path vertex shader used : " << appPath.dirPath() << shader_files.vertexFile << "\n";
                std::cout << "path vertex shader used : " << appPath.dirPath() << shader_files.fragmentFile << "\n";
            }

            meshes = init_3D_meshes_pieces(pieces_type, appPath);
            glimac::Geometry boardObj;
            boardObj.loadOBJ(appPath.dirPath()+"/assets/models/Board/Board_cube.obj",appPath.dirPath()+"/assets/models/Board/Board_cube.mtl");
            boardMesh.emplace(boardObj);
            
            camera.moveFront(-40.f);
            glEnable(GL_DEPTH_TEST); },

         .loop = [&]() {
            ImGui::ShowDemoWindow();

            renderer->bind();
            shader->bind();

            glm::mat4 viewMatrix{camera.getViewMatrix()};
            glm::mat4 projMatrix{glm::perspective(glm::radians(70.f), static_cast<float>(screen_width) / static_cast<float>(screen_height), .1f, 100.f)};


            if (boardMesh) {
                glm::mat4 boardModel = glm::mat4(1.f);
                glm::mat4 boardMV = viewMatrix * boardModel;
                shader->sendMat4("uMVPMatrix", projMatrix * boardMV);
                shader->sendMat4("uMVMatrix", boardMV);
                shader->sendMat4("uNormalMatrix", glm::transpose(glm::inverse(boardMV)));
                boardMesh->draw();
            }

            float spacing {4.0f};
            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    Piece* piece = lines[x][y];
                    if (piece == nullptr)
                        continue;

                    const Mesh& mesh_to_draw = meshes.at({piece->m_type, piece->m_is_white}); // get right mesh with type and color

                    float posX = (static_cast<float>(x) - 3.5f) * spacing;
                    float posZ = (static_cast<float>(y) - 3.5f) * spacing;

                    // transformations matrices
                    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, 0.0f, posZ));
                    glm::mat4 mvMatrix = viewMatrix * modelMatrix;
                    glm::mat4 normalMatrix{glm::transpose(glm::inverse(mvMatrix))};

                    shader->sendMat4("uMVPMatrix", projMatrix * mvMatrix);
                    shader->sendMat4("uMVMatrix", mvMatrix);
                    shader->sendMat4("uNormalMatrix", normalMatrix);

                    mesh_to_draw.draw();
                }

            }
            renderer->unbind();
            ImGui::Begin("Viewport 3D");
            {
                ImGui::BeginChild("3D render");

                ImVec2 window_size{ImGui::GetWindowSize()};
                ImGui::Image((ImTextureID)renderer->texture(), window_size, ImVec2(0, 1), ImVec2(1, 0));
                ImGui::EndChild();

                // camera rotation
                if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Right))
                {
                    ImVec2 delta{ImGui::GetIO().MouseDelta};
                    camera.rotateLeft(delta.x);
                    camera.rotateUp(delta.y);
                }
                // scroll callback
                if (ImGui::IsItemHovered())
                {
                    float wheel = ImGui::GetIO().MouseWheel;
                    if (wheel != 0.0f)
                    {
                        camera.moveFront(wheel * 0.5f);
                    }
                }

                //
            }
            ImGui::End(); }

        }
    );
}

static std::vector<Piece> init_game_2D_pieces()
{
    std::vector<Piece> game_pieces = {};
    game_pieces.reserve(32);

    // Pawns
    for (size_t i{0}; i < 8; i++)
    {
        Piece white_piece{piece_type::PAWN, true, {.x = 1, .y = static_cast<int>(i)}};
        Piece black_piece{piece_type::PAWN, false, {.x = 6, .y = static_cast<int>(i)}};

        game_pieces.push_back(white_piece);
        game_pieces.push_back(black_piece);
    }

    // Knights

    game_pieces.push_back({piece_type::KNIGHT, true, {.x = 0, .y = 1}});
    game_pieces.push_back({piece_type::KNIGHT, true, {.x = 0, .y = 6}});

    game_pieces.push_back({piece_type::KNIGHT, false, {.x = 7, .y = 1}});
    game_pieces.push_back({piece_type::KNIGHT, false, {.x = 7, .y = 6}});

    // Rooks
    game_pieces.push_back({piece_type::ROOK, true, {.x = 0, .y = 0}});
    game_pieces.push_back({piece_type::ROOK, true, {.x = 0, .y = 7}});

    game_pieces.push_back({piece_type::ROOK, false, {.x = 7, .y = 0}});
    game_pieces.push_back({piece_type::ROOK, false, {.x = 7, .y = 7}});

    // Bishops
    game_pieces.push_back({piece_type::BISHOP, true, {.x = 0, .y = 2}});
    game_pieces.push_back({piece_type::BISHOP, true, {.x = 0, .y = 5}});

    game_pieces.push_back({piece_type::BISHOP, false, {.x = 7, .y = 2}});
    game_pieces.push_back({piece_type::BISHOP, false, {.x = 7, .y = 5}});

    // Queens
    game_pieces.push_back({piece_type::QUEEN, true, {.x = 0, .y = 3}});
    game_pieces.push_back({piece_type::QUEEN, false, {.x = 7, .y = 3}});

    // Kings
    game_pieces.push_back({piece_type::KING, true, {.x = 0, .y = 4}});
    game_pieces.push_back({piece_type::KING, false, {.x = 7, .y = 4}});

    return game_pieces;
};

static std::array<std::array<Piece*, 8>, 8> construct_lines(std::vector<Piece>& pieces)
{
    std::array<std::array<Piece*, 8>, 8> board{};

    for (size_t i = 0; i < pieces.size(); i++)
    {
        int x = pieces[i].m_current_position.x;
        int y = pieces[i].m_current_position.y;

        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            board[x][y] = &pieces[i];
        }
    }
    return board;
}

int main(int argc, char** argv)
{
    std::vector<Piece>                   pieces{init_game_2D_pieces()};
    std::array<std::array<Piece*, 8>, 8> lines{construct_lines(pieces)};

    renderEverything(argv, lines);
    return 0;
}