//
// Created by adam on 8/14/21.
//

#ifndef CDETECTRON_COORDSYSTEM_H
#define CDETECTRON_COORDSYSTEM_H

#include <vector>

class CoordSystem {
public:
    CoordSystem() {
        vertices = {
            -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // x, red
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // x, red
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // y, blue
            0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // y, blue
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // z, green
            0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // z, green
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

    void draw(GLenum mode, GLsizei count) {
        init();
        glBindVertexArray(VAO);
        // Draw lines
        glDrawArrays(mode, 0, count);
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
