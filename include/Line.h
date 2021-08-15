//
// Created by adam on 8/15/21.
//

#ifndef CDETECTRON_LINE_H
#define CDETECTRON_LINE_H

class Line {
    Line(glm::vec3 start, glm::vec3 end) {
        vertices = {
            start.x, start.y, start.z,
            end.x, end.y, end.z
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
#endif // CDETECTRON_LINE_H
