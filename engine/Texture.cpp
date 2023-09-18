#include "Texture.h"
#include <GL/freeglut.h>
#include <FreeImage.h>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT        0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF


Texture::Texture(string name) : Object(name)
{
    this->path = "Texture/" + name;
    this->texId = getId();
#ifdef _WINDOWS 
    loadBitmapFromFile();
#endif
}

Texture::~Texture()
{
	cout << "[Destroyed TEXTURE: " << Texture::getName() << "(" << Texture::texId << ")" << "]" << endl;
    glDeleteTextures(1, &texId);
}

void Texture::loadBitmapFromFile()
{
        // Create OpenGL texture:
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);

        // Set circular coordinates:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set anisotropic filtering:
        float maxAnisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

        // Change texture settings:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Load effective texture from file into bitmap:
        FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(path.c_str(), 0), path.c_str());

        if (!bitmap)
        {
            cout << "Error loading the texture image " << getName() << "("<< getId() << ") path: " << path << endl;
            initialized = false;
            return;
        }

        FreeImage_FlipVertical(bitmap);

        // Converting to use RGBA:
        bitmap = FreeImage_ConvertTo32Bits(bitmap);

        // Load image into OpenGL:
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));

        // Unload bitmap:
        FreeImage_Unload(bitmap);

        initialized = true;
}

void Texture::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
    if (!initialized)
        loadBitmapFromFile();
    else
        glBindTexture(GL_TEXTURE_2D, texId);
}
