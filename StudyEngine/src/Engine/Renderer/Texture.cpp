#include "../../Headers.h"

#include "Texture.h"
#include "Renderer.h"

#include "../../Platform/OpenGL/OpenGLTexture.h"

namespace Study{
    Shared<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {

        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!");
        case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture>(width, height);
        }

        STUDY_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Shared<Texture2D> Texture2D::Create(const std::string& path){

        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!");
        case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture>(path);
        }

        STUDY_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;

    }

}