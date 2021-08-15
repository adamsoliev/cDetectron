// Third party
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// STL
#include <iostream>

// Project
#include "CameraManager.h"
#include "CoordSystem.h"
#include "GeneralBox.h"
#include "LightSource.h"
#include "PlaneTextured.h"
#include "Setup.h"
#include "ShaderManager.h"
#include "TextureManager.h"

int main() {

    Setup setup;

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // global opengl states
    glEnable(GL_DEPTH_TEST);

    ShaderManager woodBoxShader("./assets/shaders/advanced.vert",
                            "./assets/shaders/advanced.frag");

    ShaderManager lightSourceShader("./assets/shaders/lightSource.vert",
                                 "./assets/shaders/lightSource.frag");

    ShaderManager coordSystemShader("./assets/shaders/basic.vert",
                                 "./assets/shaders/basic.frag");

    // **********
    ShaderManager planeShader("./assets/shaders/advanced.vert",
                              "./assets/shaders/advanced.frag");

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(4.0f, 0.0f, 0.0f)
    };


    TextureManager woodTexture("assets/images/container.jpg");
    TextureManager grassTexture("assets/images/grass.png");

    woodBoxShader.use();
    woodBoxShader.setInt("textureGeneral", 0);

    planeShader.use();
    planeShader.setInt("textureGeneral", 1);

    CoordSystem coordSystem;

    GeneralBox woodBox;
    LightSource lightSource;
    // PlaneTextured planeTextured;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(setup._window)) {

        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(setup._window);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // also clear the depth buffer now!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        lightSourceShader.use();
        glm::vec3 lightPos(0.0f, 5.0f, 5.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        lightSourceShader.setMat4("projection", projection);
        lightSourceShader.setMat4("view", view);
        lightSourceShader.setMat4("model", model);
        lightSource.draw(GL_TRIANGLES, 36);

        // render boxes
        woodBoxShader.use();
        woodBoxShader.setVec3("light_color", glm::vec3(1.0f));
        woodBoxShader.setVec3("light_pos", lightPos);
        woodBoxShader.setVec3("view_pos", camera.Position);

        for (int i = 0; i < 2; ++i) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime(),
                                glm::vec3(0.0f, 1.0f, 0.0f));
            woodBoxShader.setMat4("model", model);
            woodBoxShader.setMat4("projection", projection);
            woodBoxShader.setMat4("view", view);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, woodTexture.texture);

            woodBox.draw(GL_TRIANGLES, 36);
        }

        /*
        planeShader.use();
        planeShader.setVec3("light_color", glm::vec3(1.0f));
        planeShader.setVec3("light_pos", lightPos);
        planeShader.setVec3("view_pos", camera.Position);

        glm::vec3 scale = glm::vec3(10.0f, 10.0f, 10.0f);
        model = glm::mat4(1.0f);
        model = glm::scale(model, scale);

        planeShader.setMat4("projection", projection);
        planeShader.setMat4("view", view);
        planeShader.setMat4("model", model);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, grassTexture.texture);

        planeTextured.draw(GL_TRIANGLES, 6);
         */

        coordSystemShader.use();
        model = glm::mat4(1.0f);
        glm::vec3 scale = glm::vec3(10.0f, 10.0f, 10.0f);
        model = glm::scale(model, scale);

        coordSystemShader.setMat4("projection", projection);
        coordSystemShader.setMat4("view", view);
        coordSystemShader.setMat4("model", model);

        coordSystem.draw(GL_LINES, 6);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        setup.update();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    coordSystem.cleanUp();
    woodBox.cleanUp();
    lightSource.cleanUp();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    setup.terminate();
    return 0;
}
