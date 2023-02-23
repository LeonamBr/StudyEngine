#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include "../../Engine/Renderer/Texture.h"
#include <GLAD/glad/glad.h>

namespace Study {

    class OpenGLTexture : public Texture2D{

        public:

            OpenGLTexture(uint32_t width, uint32_t height);
            OpenGLTexture(const std::string& path);
            virtual ~OpenGLTexture();

            virtual uint32_t GetWidth() const override { return m_Width; }
            virtual uint32_t GetHeight() const override { return m_Height; }

            virtual void SetData(void* data, uint32_t size) override;

            virtual void Bind(uint32_t slot = 0) const override;

        private:

            std::string m_Path;
            uint32_t m_Width;
            uint32_t m_Height;
            uint32_t m_RendererID;
            GLenum m_InternalFormat;
            GLenum m_DataFormat;

    };
    
}

#endif