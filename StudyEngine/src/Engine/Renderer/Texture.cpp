#include "../../Headers.h"

#include "Texture.h"
#include "Renderer.h"

#include "../../Platform/OpenGL/OpenGLTexture.h"

namespace Study{

    Shared<Texture2D> Texture2D::Create(const std::string& path){

        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!");
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(path);
        }

        STUDY_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;

    }

}