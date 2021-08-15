//
// Created by adam on 8/14/21.
//

#ifndef CDETECTRON_GENERALBOX_H
#define CDETECTRON_GENERALBOX_H

class GeneralBox {
public:
    GeneralBox() {
        vertices = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
            0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
            0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
            0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
            -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
            0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
            -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,

            -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
            0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
            0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
            0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
            0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
            0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
            0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

            -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
            -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
            -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f
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

#endif // CDETECTRON_GENERALBOX_H

