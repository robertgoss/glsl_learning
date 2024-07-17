// Basic torus model rendering to test lighting shaders

// Chapter 3

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../setup.h"
#include "../vertex_buffer_creator.h"

#include <cstring>

// All based on OpenGL4 Shading Language cookbook, David Wolff.

void tumble_torus_main(const std::vector<std::string> &args) {
    GLFWwindow* window = initWindow();

    std::string shader = "two_side_phong_discard";
    if (args.size() > 1) {
        shader = args[1];
    }
    std::string shader_path = shader + ".vert.glsl";

    std::string frag_path = "basic.frag.glsl";
    if (shader == "two_side_phong") {
        frag_path = "two_sided_basic.frag.glsl";
    } else if (shader == "two_side_phong_discard") {
        frag_path = "two_sided_discard.frag.glsl";
    }

    GLuint vertShader = loadShader(shader_path, GL_VERTEX_SHADER);
    GLuint fragShader = loadShader(frag_path, GL_FRAGMENT_SHADER);
    GLuint programHandle = makeProgram({vertShader, fragShader});

    // Query for each offset
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(1.0f,0.0f,0.0f));
    model = glm::rotate(model, glm::radians(35.0f), glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));

    glm::vec4 worldLight = glm::vec4(5.0f,5.0f,2.0f,1.0f);
    glm::vec3 Kd = glm::vec3(0.9f, 0.5f, 0.3f);
    glm::vec3 Ld = glm::vec3(1.0f, 1.0f, 1.0f);

    if (shader == "diffuse") {
        setUniform(programHandle, "Kd", Kd);
        setUniform(programHandle, "Ld", Ld);
        setUniform(programHandle, "LightPosition", view * worldLight);
    } else if (shader == "phong" || shader == "two_side_phong" || shader == "two_side_phong_discard") {
        glm::vec3 Ka = glm::vec3(0.9f, 0.5f, 0.3f);
        glm::vec3 La = glm::vec3(0.4f, 0.4f, 0.4f);
        glm::vec3 Ks = glm::vec3(0.8f, 0.8f, 0.8f);
        glm::vec3 Ls = glm::vec3(1.0f, 1.0f, 1.0f);
        setUniform(programHandle, "Material.Kd", Kd);
        setUniform(programHandle, "Light.Ld", Ld);
        setUniform(programHandle, "Light.Position", view * worldLight );
        setUniform(programHandle, "Material.Ka", Ka);
        setUniform(programHandle, "Light.La", La);
        setUniform(programHandle, "Material.Ks", Ks);
        setUniform(programHandle, "Light.Ls", Ls);
        setUniform(programHandle, "Material.Shininess", 100.0f);
    }
    // Setup the triangle data
    GLuint count = 0;
    std::string geometry = "torus";
    if (!args.empty()) {
        geometry = args[0];
    }
    GLuint vaoHandle = VertexBufferCreator::named(geometry, count);

    float angle = 0.0f;

    RenderCallback callback = [&](float _time, const glm::mat4 proj) {
        angle += 0.01;
        if (angle > 360) {
            angle -= 360;
        }
        double angle2 = angle * 1.45;
        if (angle2 > 360) {
            angle2 -= 360;
        }

        model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,cos(angle2),sin(angle2)));

        glm::mat4 mv = view * model;
        setUniform(programHandle, "ModelViewMatrix", mv);
        setUniform(programHandle, "NormalMatrix",
                   glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]) ));
        setUniform(programHandle, "MVP", proj * mv);

        glBindVertexArray(vaoHandle);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    };

    render(window, true,callback);
}