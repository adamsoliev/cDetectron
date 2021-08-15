// Source: https://learnopengl.com/Getting-started/Coordinate-Systems

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
#include <math.h>

// Project
#include "CameraManager.h"
#include "ShaderManager.h"
#include "CoordSystem.h"
#include "GeneralBox.h"
#include "LightSource.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
CameraManager camera(glm::vec3(-9.0f, 5.0f, 8.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    ShaderManager ourShader("./assets/shaders/advanced.vert",
                            "./assets/shaders/advanced.frag");

    ShaderManager lightingShader("./assets/shaders/lightSource.vert",
                                 "./assets/shaders/lightSource.frag");

    ShaderManager planeBasic("./assets/shaders/basic.vert",
                                 "./assets/shaders/basic.frag");

    // **********
    ShaderManager planeShader("./assets/shaders/advanced.vert",
                              "./assets/shaders/advanced.frag");

    float vPlane[] = {
        -0.5f, 0.0f, -0.5f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.0f, -0.5f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f, -0.5f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int vboP, vaoP;
    glGenVertexArrays(1, &vaoP);
    glGenBuffers(1, &vboP);

    glBindVertexArray(vaoP);

    glBindBuffer(GL_ARRAY_BUFFER, vboP);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vPlane), vPlane, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // normal coord attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // **********

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(-4.0f, 0.0f, 0.0f),
        glm::vec3(4.0f, 3.0f, 5.0f)
    };

    // load and create a texture
    // -------------------------
    unsigned int textureBox, texturePlane;
    // texture 1
    // ---------
    glGenTextures(1, &textureBox);
    glBindTexture(GL_TEXTURE_2D, textureBox);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("./assets/images/container.jpg", &width,
                                    &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texturePlane);
    glBindTexture(GL_TEXTURE_2D, texturePlane);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width2, height2, nrChannels2;
    // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data2 = stbi_load("./assets/images/grass.png", &width2,
                                    &height2, &nrChannels2, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);

    // tell opengl for each sampler to which texture unit it belongs to (only
    // has to be done once)
    // -------------------------------------------------------------------------------------------

    // -----------------------------------------------------------------------
    // SHADERS
    // -----------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("textureGeneral", 0);

    planeShader.use();
    planeShader.setInt("textureGeneral", 1);

    CoordSystem coordSystem;

    GeneralBox woodBox;
    LightSource lightSource;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {

        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // also clear the depth buffer now!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureBox);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texturePlane);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        lightingShader.use();
        glm::vec3 lightPos(0.0f, 5.0f, 5.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("model", model);
        lightSource.draw(GL_TRIANGLES, 36);

        // render boxes
        ourShader.use();
        ourShader.setVec3("light_color", glm::vec3(1.0f));
        ourShader.setVec3("light_pos", lightPos);
        ourShader.setVec3("view_pos", camera.Position);

        for (int i = 0; i < 2; ++i) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime(),
                                glm::vec3(0.0f, 1.0f, 0.0f));
            ourShader.setMat4("model", model);
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);
            woodBox.draw(GL_TRIANGLES, 36);
        }
        // *********************
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
        glBindVertexArray(vaoP);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // *********************

        planeBasic.use();
        model = glm::mat4(1.0f);
        scale = glm::vec3(15.0f, 15.0f, 15.0f);
        model = glm::scale(model, scale);

        planeBasic.setMat4("projection", projection);
        planeBasic.setMat4("view", view);
        planeBasic.setMat4("model", model);

        coordSystem.draw(GL_LINES, 6);

        /*
        std::cout << "************* CAMERA ***************" << std::endl;
        std::cout << "POSITION: " << glm::to_string(camera.Position) <<
         std::endl;
        std::cout << "UP: " << glm::to_string(camera.Up) << std::endl;
        std::cout << "YAW: " << camera.Yaw << std::endl;
        std::cout << "PITCH: " << camera.Pitch << std::endl;
        std::cout << "************* CAMERA ***************" << std::endl;
         */

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    coordSystem.cleanUp();
    woodBox.cleanUp();
    lightSource.cleanUp();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset =
        lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}