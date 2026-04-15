// #include <glad/glad.h>
// #include <glimac/FilePath.hpp>
// #include <glimac/FreeflyCamera.hpp>
#include <glad/glad.h>
#include <imgui.h>
#include <exception>
#include <glimac/FilePath.hpp>
#include <vector>
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "glimac/TrackballCamera.hpp"
#include "glimac/common.hpp"
#include "quick_imgui/quick_imgui.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glimac/Geometry.hpp>
#include <glimac/Sphere.hpp>
#include <iostream>

const unsigned int screen_width{800};
const unsigned int screen_height{800};

int main(int argc, char** argv)
{
    // FreeflyCamera    camera{};
    TrackballCamera camera{};
    // ThreeDRenderer   renderer{};
    // glimac::FilePath appPath(argv[0]);

    std::optional<Renderer> renderer;
    std::optional<Shader>   shader;
    std::optional<Mesh>     mesh;
    // glimac::Geometry        cube;

    glimac::FilePath appPath(argv[0]);
    ShaderFile       shader_files{.vertexFile = "/assets/shaders/3D.vs.glsl", .fragmentFile = "/assets/shaders/normals.fs.glsl"};

    quick_imgui::loop(
        "Chessimac",
        {
            .init = [&]() {
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

                glimac::Sphere   sphere(1, 32, 16);
                glimac::Geometry cube{};

                cube.loadOBJ(appPath.dirPath() + "/assets/models/cube.obj", appPath.dirPath() + "/assets/models/cube.mtl", true);

                mesh.emplace(cube);

                glEnable(GL_DEPTH_TEST);

                //  mesh.emplace(sphere.getVertexCount(), sphere.getDataPointer()); },
                //   mesh.emplace(cube.getVertexCount(), cube.getDataPointer()); },
            },

            .loop = [&]() {
                                ImGui::ShowDemoWindow();
                            
                                renderer->bind();
                                shader->bind();
                                
                                glm::mat4 ProjMatrix{glm::perspective(glm::radians(70.f),
                                                                    static_cast<float>(screen_width) /
                                                                        static_cast<float>(screen_height),
                                                                    .1f, 100.f)};
                                glm::mat4 MVMatrix{
                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -5.f))};
                                glm::mat4 NormalMatrix{glm::transpose(glm::inverse(MVMatrix))};
                                
                                shader->sendMat4("uMVPMatrix", ProjMatrix*MVMatrix);
                                shader->sendMat4("uMVMatrix", MVMatrix);
                                shader->sendMat4("uNormalMatrix", NormalMatrix);

                                mesh->draw();
                                // cube.draw();
                                
                                renderer->unbind();

                                ImGui::Begin("Viewport 3D");
                                {
                                    ImGui::BeginChild("3D render");
                                    ImVec2 window_size {ImGui::GetWindowSize()};
                                    ImGui::Image((ImTextureID)renderer->texture(), window_size, ImVec2(0,1), ImVec2(1,0));
                                    ImGui::EndChild();
                                }
                                ImGui::End(); },

            // .onScroll = [&](double /*xoffset*/, double yoffset) { camera.moveFront(static_cast<float>(yoffset) * 0.5f); },
        }
    );

    return 0;
}