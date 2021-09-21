#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "Shader.h"
#include "Drawables/Triangle.h"
#include "Drawables/Scene.h"
#include "Maths/MatrixFactory.h"

Drawables::Scene scene{};
Shader shader;

enum class InputAction {Forward, Backward, Left, Right, Upward, Downward, RotateUp, RotateDown, RotateLeft, RotateRight};
std::vector<InputAction> currentActions{};

const float MOVE_SPEED = 0.00000000000009f;
const float ROTATE_SPEED = 0.00000000000007f;

const std::string SCENE_FILE = "src\\Scenes\\Obj.scene";

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& shape : scene.shapes)
    {
        shader.setUniform("model", shape->transform);
        shader.setUniform("mAmbient", shape->material.ambient);
        if (shape->material.diffuseMap && shape->material.diffuseMap->isLoaded())
        {
            shape->material.diffuseMap->setActive();
        }
        shape->draw();
    }

    for (auto& object : scene.objects)
    {
        shader.setUniform("model", Maths::Matrix4{});
        if (object->getTextureID() != -1)
        {
            scene.textures[object->getTextureID()]->setActive();
        }
        object->draw();
    }
}

void handleInput(double elapsedTime)
{
    for (auto& action : currentActions)
    {
        
        switch (action)
        {
        case InputAction::Forward:
            scene.camera.move(scene.camera.getDirection() * MOVE_SPEED * elapsedTime);
            break;

        case InputAction::Backward:
            scene.camera.move(scene.camera.getDirection() * -MOVE_SPEED * elapsedTime);
            break;

        case InputAction::Left:
            scene.camera.move(scene.camera.getRight() * MOVE_SPEED * elapsedTime);
            break;

        case InputAction::Right:
            scene.camera.move(scene.camera.getRight() * -MOVE_SPEED * elapsedTime);
            break;

        case InputAction::Upward:
            scene.camera.move(Maths::Vector3{0, 1, 0} *MOVE_SPEED * elapsedTime);
            break;

        case InputAction::Downward:
            scene.camera.move(Maths::Vector3{ 0, 1, 0 } * -MOVE_SPEED * elapsedTime);
            break;

        case InputAction::RotateDown:
            scene.camera.rotateX(-ROTATE_SPEED * elapsedTime);
            break;

        case InputAction::RotateUp:
            scene.camera.rotateX(ROTATE_SPEED * elapsedTime);
            break;

        case InputAction::RotateLeft:
            scene.camera.rotateY(ROTATE_SPEED * elapsedTime);
            break;

        case InputAction::RotateRight:
            scene.camera.rotateY(-ROTATE_SPEED * elapsedTime);
            break;

            break;
        }
    }

    Maths::Matrix4 view = Maths::MatrixFactory::lookInDirection(scene.camera.getPosition(), scene.camera.getDirection(), scene.camera.getUp());
    shader.setUniform("view", view);
    currentActions.clear();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(512, 512, "OpenGL 3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
            scene.camera.setAspectRatio((float)width / (float)height);
            Maths::Matrix4 projection = Maths::MatrixFactory::perspective(scene.camera.getHeightAngle(), scene.camera.getAspectRatio(),
                0.1f, 100.0f);
            shader.setUniform("projection", projection);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (glfwGetKey(window, GLFW_KEY_W))
            {
                currentActions.push_back(InputAction::Forward);
            }
            if (glfwGetKey(window, GLFW_KEY_S))
            {
                currentActions.push_back(InputAction::Backward);
            }
            if (glfwGetKey(window, GLFW_KEY_A))
            {
                currentActions.push_back(InputAction::Left);
            }
            if (glfwGetKey(window, GLFW_KEY_D))
            {
                currentActions.push_back(InputAction::Right);
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE))
            {
                currentActions.push_back(InputAction::Upward);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            {
                currentActions.push_back(InputAction::Downward);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT))
            {
                currentActions.push_back(InputAction::RotateLeft);
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT))
            {
                currentActions.push_back(InputAction::RotateRight);
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN))
            {
                currentActions.push_back(InputAction::RotateDown);
            }
            if (glfwGetKey(window, GLFW_KEY_UP))
            {
                currentActions.push_back(InputAction::RotateUp);
            }
        });

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR" << std::endl;

    glClearColor(0, 0, 0, 1);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    std::cout << glGetString(GL_VERSION) << std::endl;
    

    scene.read(SCENE_FILE);

    shader = { scene.vert, scene.frag };
    shader.createShaders();
    shader.useShader();

    Maths::Matrix4 projection = Maths::MatrixFactory::perspective(scene.camera.getHeightAngle(), scene.camera.getAspectRatio(), 0.1f, 100);
    Maths::Matrix4 view = Maths::MatrixFactory::lookInDirection(scene.camera.getPosition(), scene.camera.getDirection(), scene.camera.getUp());

    shader.setUniform("projection", projection);
    shader.setUniform("view", view);
    shader.setUniform("tex", 0);
   
    shader.setUniform("sAmbient", scene.ambient);

    // apply lighting
    if (scene.lights.size() > 0)
    {
        shader.setUniform("lightColour", scene.lights[0]->colour);
        shader.setUniform("lightPos", scene.lights[0]->position);
        std::shared_ptr<Lighting::PointLight> pointLight = std::dynamic_pointer_cast<Lighting::PointLight>(scene.lights[0]);
        if (pointLight)
        {
            shader.setUniform("constantAttenuation", pointLight->constantAttenuation);
            shader.setUniform("linearAttenuation", pointLight->linearAttenuation);
            shader.setUniform("quadraticAttenuation", pointLight->quadraticAttenuation);
        }
    }

    for (auto& texture : scene.textures)
    {
        texture->init();
    }

    for (auto& shape : scene.shapes)
    {
        shape->init();
    }

    for (auto& object : scene.objects)
    {
        object->init();
    }

    double lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        double elapsedTime = currentTime - lastTime;
        
        lastTime = currentTime;

        //convert elapsedTime to seconds
        elapsedTime /= 1000.0;

        /* Render here */
        draw();

        handleInput(currentTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}