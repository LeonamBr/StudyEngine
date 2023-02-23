#include "../../Headers.h"

#include <stb_image/stb_image.h>

#include "OpenGLTexture.h"


namespace Study{

    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
    {

        STUDY_PROFILE_FUNCTION();

        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;


        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);


    }

    OpenGLTexture::OpenGLTexture(const std::string& path) : m_Path(path)
    {

        STUDY_PROFILE_FUNCTION();

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = nullptr;

        { 
            STUDY_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string &path)");

            data = stbi_load(path.c_str(), &width, &height, & channels, 0);
        }

        STUDY_CORE_ASSERT(data, "Can't load a image!");
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;

        if (channels == 4){
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if ( channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        STUDY_CORE_ASSERT(internalFormat && dataFormat, "Format is not suported");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);

    }

    OpenGLTexture::~OpenGLTexture()
    {

        STUDY_PROFILE_FUNCTION();

        glDeleteTextures(1, &m_RendererID);

    }

    void OpenGLTexture::SetData(void *data, uint32_t size)
    {

        STUDY_PROFILE_FUNCTION();

        uint32_t bitsPerChannel = m_DataFormat == GL_RGBA ? 4 : 3;
        STUDY_CORE_ASSERT(size == m_Width * m_Height * bitsPerChannel, "Data must be entire texture!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

    }

    void OpenGLTexture::Bind(uint32_t slot) const
    {

        STUDY_PROFILE_FUNCTION();

        glBindTextureUnit(slot, m_RendererID);

    }
}
