#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <axolote/engine.hpp>

#define G 6.67e-11

class CelestialBody : public axolote::Entity
{
public:
    bool is_light_emissor = false;
    double mass;
    glm::vec3 velocity;
    glm::vec3 pos;

    CelestialBody(double mass, const glm::vec3 &velocity);

    glm::vec3 calculate_acceleration(const CelestialBody &other);
    void update(double dt) override;
    void draw() override;
};

CelestialBody::CelestialBody(double mass, const glm::vec3 &velocity) :
    mass{mass},
    velocity{velocity}
{
}

glm::vec3 CelestialBody::calculate_acceleration(const CelestialBody &other)
{
    glm::vec3 direction = glm::normalize(pos - other.pos);
    double r = glm::distance(pos, other.pos);
    std::cout << r << std::endl;
    float gravitational_acceleration = (G * mass) / (r * r);
    return direction * gravitational_acceleration;
}

void CelestialBody::update(double dt)
{
    glm::mat4 mat{1.0f};
    set_matrix(0, mat);
}

void CelestialBody::draw()
{
    for (auto &e : objects)
    {
        for (auto &e2 : e.meshes)
        {
            e2.shader.activate();
            e2.shader.set_uniform_int("is_light_color_set", !is_light_emissor);
        }
    }

    Entity::draw();

    for (auto &e : objects)
    {
        for (auto &e2 : e.meshes)
        {
            e2.shader.activate();
            e2.shader.set_uniform_int("is_light_color_set", 0);
        }
    }
};

class App : public axolote::Window
{
public:
    void main_loop();
};

void App::main_loop()
{
    camera.speed = 0.3f;
    camera.sensitivity = 10000.0f;

    std::string original_title = title();

    axolote::Shader shader_program("./resources/shaders/def_vertex_shader.glsl",
                                   "./resources/shaders/def_fragment_shader.glsl");

    shader_program.activate();
    shader_program.set_uniform_float("ambient", 0.05f);
    shader_program.set_uniform_float4("light_color", 1.0f, 1.0f, 1.0f, 1.0f);
    shader_program.set_uniform_float3("light_pos", 0.0f, 0.0f, 0.0f);

    glm::mat4 mat{1.0f};
    mat = glm::scale(mat, glm::vec3{0.3f, 0.3f, 0.3f});
    CelestialBody earth{5.97e24, glm::vec3(0.0f, 0.0f, 29.78e3)};
    axolote::Object3D earthobj{"./resources/models/sphere/sphere.obj", glm::vec3(0.0f, 0.0f, 1.0f), mat};
    earth.pos = glm::vec3{5.0f, 0.0f, 0.0f};
    earth.add_object(earthobj);
    earth.bind_shader_at(0, shader_program);

    mat = glm::mat4{1.0f};
    CelestialBody sun{1.98e30, glm::vec3{0.0, 0.0, 35e3}};
    axolote::Object3D sunobj{"./resources/models/sphere/sphere.obj", glm::vec3(1.0f, 1.0f, 0.5f), mat};
    sun.pos = glm::vec3{0.0f, 0.0f, 5.0f};
    sun.is_light_emissor = true;
    sun.add_object(sunobj);
    sun.bind_shader_at(0, shader_program);

    glm::vec3 res = earth.calculate_acceleration(sun);
    std::cout << res.x << std::endl
              << res.y << std::endl
              << res.z << std::endl;
    std::cout << glm::length(res) << std::endl;



    axolote::Scene scene{};
    scene.add_drawable(&earth);
    scene.add_drawable(&sun);

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

        scene.camera = camera;
        scene.update_camera((float)width() / height());
        scene.update(dt);
        scene.render();

        std::stringstream sstr;
        sstr << original_title << " | " << (int)(1 / dt) << " fps";
        set_title(sstr.str());

        glfwSwapBuffers(window);
    }
}

int main()
{
    std::cout << "Solar System 3D" << std::endl;
    App app{};
    app.set_title("Uepa");
    app.set_color(0x10, 0x10, 0x10);
    app.main_loop();
    return 0;
}










