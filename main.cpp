#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <string>

// All based on OpenGL4 Shading Language cookbook, David Wolff.

// Scenes
extern void spinning_triangle_main(const std::vector<std::string> &args);
extern void fragment_circle_main(const std::vector<std::string> &args);
extern void tumble_torus_main(const std::vector<std::string> &args);

using MainFunc = void(*)(const std::vector<std::string>& args);

int main(int argc, const char** argv) {
    std::string scene = "tumble_torus";
    if(argc > 1) {
        scene = argv[1];
    }
    std::vector<std::string> args;
    for (int i = 2; i < argc; ++i) {
        args.emplace_back(argv[i]);
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
    sceneFunc(args);

}
