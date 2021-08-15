//
// Created by adam on 8/14/21.
//

#ifndef CDETECTRON_TEXTUREMANAGER_H
#define CDETECTRON_TEXTUREMANAGER_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class TextureManager {
public:
    unsigned int texture;

    TextureManager(const char* textureImagePath) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
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
        unsigned char *data = stbi_load(textureImagePath, &width,
                                        &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
};

#endif // CDETECTRON_TEXTUREMANAGER_H
