//
// Created by adam on 8/14/21.
//

#ifndef CDETECTRON_COORDSYSTEM_H
#define CDETECTRON_COORDSYSTEM_H

#include "Line.h"

#include <vector>

class CoordSystem {
public:
    CoordSystem() {
        vertices = {
            -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // x, red
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // x, red
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // y, green
            0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // y, green
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // z, blue
            0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // z, blue

            // x plane lines
            1.0f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.9f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.9f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.8f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.8f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.7f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.7f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.6f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.6f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.5f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.5f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.4f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.4f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.3f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.3f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.2f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.2f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.1f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.1f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            0.0f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.1f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.1f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.2f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.2f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.3f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.3f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.4f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.4f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.5f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.5f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.6f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.6f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.7f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.7f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.8f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.8f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -0.9f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -0.9f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,

            // z plane lines
            1.0f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.9f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.9f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.8f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.8f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.7f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.7f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.6f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.6f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.5f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.5f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.4f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.4f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.3f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.3f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.2f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.2f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.1f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.1f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, 0.0f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, 0.0f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.1f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.1f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.2f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.2f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.3f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.3f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.4f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.4f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.5f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.5f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.6f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.6f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.7f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.7f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.8f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.8f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -0.9f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -0.9f, 0.3f, 0.3f, 0.3f,
            1.0f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
            -1.0f, 0.0f, -1.0f, 0.3f, 0.3f, 0.3f,
        };
    }

    void init() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(),
                     vertices.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void *)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void draw(GLenum mode) {
        init();
        glBindVertexArray(VAO);
        // Draw lines
        glDrawArrays(mode, 0, vertices.size() / 6);
    }

    void cleanUp() {
        // Clean up
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

private:
    std::vector<float> vertices;
    unsigned int VAO{}, VBO{};

};

#endif // CDETECTRON_COORDSYSTEM_H
