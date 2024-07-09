#include <string>
#include <map>
#include <iostream>

// All based on OpenGL4 Shading Language cookbook, David Wolff.

// Scenes
extern void spinning_triangle_main();
extern void fragment_circle_main();
extern void tumble_torus_main();

using MainFunc = void(*)();

int main(int argc, const char** argv) {
    std::string scene = "tumble_torus";
    if(argc > 1) {
        scene = argv[1];
    }
    std::map<std::string, MainFunc> scenes = {
            {"spinning_triangle", &spinning_triangle_main},
            {"fragment_circle", &fragment_circle_main},
            {"tumble_torus", &tumble_torus_main}
    };

    auto sceneIt = scenes.find(scene);
    if (sceneIt == scenes.end()) {
        std::cerr << "Unable to find scene " << scene << std::endl;
        exit(EXIT_FAILURE);
    }

    MainFunc sceneFunc = sceneIt->second;
    sceneFunc();

}
