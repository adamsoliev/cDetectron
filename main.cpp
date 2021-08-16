// Third party
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
#include "Mesh.h"
#include "Model.h"

int main() {

    Setup setup;

    gladLoadGL();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(setup._window, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // global opengl states
    glEnable(GL_DEPTH_TEST);

    ShaderManager woodBoxShader("./assets/shaders/advanced.vert",
                            "./assets/shaders/advanced.frag");

    ShaderManager modelShader("./assets/shaders/model.vert",
                                "./assets/shaders/model.frag");

    ShaderManager lightSourceShader("./assets/shaders/lightSource.vert",
                                 "./assets/shaders/lightSource.frag");

    ShaderManager coordSystemShader("./assets/shaders/basic.vert",
                                 "./assets/shaders/basic.frag");

    /*
    ShaderManager planeShader("./assets/shaders/advanced.vert",
    "./assets/shaders/advanced.frag");
     */

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(-4.0f, 1.0f, 0.0f),
        glm::vec3(4.0f, 2.0f, 0.0f)
    };


    TextureManager woodTexture("assets/images/container.jpg");
    TextureManager grassTexture("assets/images/grass.png");

    woodBoxShader.use();
    woodBoxShader.setInt("textureGeneral", 0);

    /*
    planeShader.use();
    planeShader.setInt("textureGeneral", 1);
     */

    CoordSystem coordSystem;

    GeneralBox woodBox;
    LightSource lightSource;
    PlaneTextured planeTextured;

    Model ourModel("assets/models/backpack/backpack.obj");

    // render loop
    while (!glfwWindowShouldClose(setup._window)) {

        setup.updateCamera();

        // input
        processInput(setup._window);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // also clear the depth buffer now!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // render light source box
        lightSourceShader.use();
        glm::vec3 lightPos(0.0f, 2.0f, 5.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        lightSourceShader.setMat4("projection", projection);
        lightSourceShader.setMat4("view", view);
        lightSourceShader.setMat4("model", model);
        lightSource.draw(GL_TRIANGLES, 36);

        // render wood box
        woodBoxShader.use();
        woodBoxShader.setVec3("light_color", glm::vec3(1.0f));
        woodBoxShader.setVec3("light_pos", lightPos);
        woodBoxShader.setVec3("view_pos", camera.Position);

        for (auto & cubePosition : cubePositions) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePosition);
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
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 4.0f)); //
        model = glm::scale(model, scale);

        planeShader.setMat4("projection", projection);
        planeShader.setMat4("view", view);
        planeShader.setMat4("model", model);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, grassTexture.texture);

        planeTextured.draw(GL_TRIANGLES, 6);
         */


        // render coord system
        coordSystemShader.use();
        model = glm::mat4(1.0f);
        glm::vec3 scale = glm::vec3(10.0f, 10.0f, 10.0f);
        model = glm::scale(model, scale);

        coordSystemShader.setMat4("projection", projection);
        coordSystemShader.setMat4("view", view);
        coordSystemShader.setMat4("model", model);

        coordSystem.draw(GL_LINES);

        // render the loaded model
        modelShader.use();
        model = glm::mat4(1.0f);
        static glm::vec3 translateModel = glm::vec3(0.0f, 3.0f, 0.0f);
        model = glm::translate(model, translateModel); //
        model = glm::rotate(model, (float)glfwGetTime(),
                            glm::vec3(0.0f, 1.0f, 0.0f));
        static glm::vec3 scaleModel = glm::vec3(0.6f, 0.6f, 0.6f);
        model = glm::scale(model, scaleModel);	// it's a bit
        modelShader.setMat4("model", model);
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);

        modelShader.setVec3("light_color", glm::vec3(1.0f));
        modelShader.setVec3("light_pos", lightPos);
        modelShader.setVec3("view_pos", camera.Position);

        ourModel.Draw(modelShader);

        {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Model Translate");
            ImGui::SliderFloat("xT", &translateModel.x, -10.0f, 10.0f);
            ImGui::SliderFloat("yT", &translateModel.y, -10.0f, 10.0f);
            ImGui::SliderFloat("zT", &translateModel.z, -10.0f, 10.0f);

            ImGui::Text("Model Scale");
            ImGui::SliderFloat("xS", &scaleModel.x, -10.0f, 10.0f);
            ImGui::SliderFloat("yS", &scaleModel.y, -10.0f, 10.0f);
            ImGui::SliderFloat("zS", &scaleModel.z, -10.0f, 10.0f);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        setup.update();
    }

    // ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // optional: de-allocate all resources once they've outlived their purpose:
    coordSystem.cleanUp();
    woodBox.cleanUp();
    lightSource.cleanUp();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    setup.terminate();
    return 0;
}
