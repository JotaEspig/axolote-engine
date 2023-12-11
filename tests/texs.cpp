#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <axolote/engine.hpp>

class App : public axolote::Window
{
public:
    void main_loop();
};

void App::main_loop()
{
    std::string original_title = title();

    axolote::Shader shader_program(
        "./resources/shaders/def_vertex_shader.glsl",
        "./resources/shaders/def_fragment_shader.glsl"
    );

    shader_program.activate();
    shader_program.set_uniform_int("light.is_set", 0);
    // Scene object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    scene->camera.pos = {0.0f, 0.0f, 5.0f};
    scene->camera.speed = 3.0f;
    scene->camera.sensitivity = 10000.0f;

    std::shared_ptr<axolote::Object3D> body{new axolote::Object3D{
        "./resources/models/m26/m26pershing_coh.obj",
        {1.0f, 1.0f, 1.0f},
        glm::mat4{1.0f}}};
    body->bind_shader(shader_program);
    scene->add_drawable(body);

    current_scene = scene;
    double before = glfwGetTime();
    while (!should_close())
    {
        glClearColor(_color.r, _color.g, _color.b, _color.opacity);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        double now = glfwGetTime();
        double dt = now - before;
        before = now;
        process_input(dt);

        std::stringstream sstr;
        sstr << original_title << " | " << (int)(1 / dt) << " fps";
        set_title(sstr.str());

        scene->update_camera((float)width() / height());
        scene->update(dt);
        scene->render();

        glfwSwapBuffers(window);
    }
}

int main()
{
    std::cout << "Tests" << std::endl;
    App app{};
    app.set_title("Uepa");
    app.set_width(600);
    app.set_height(600);
    app.set_color(0x10, 0x10, 0x10);
    app.main_loop();
    return 0;
}
