#include "../../Headers.h"

#include "Shader.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLShader.h"

namespace Study {
    Shader *Shader::Create(const std::string path)
    {
        switch(Renderer::GetAPI()){

            case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(path);

        }


        STUDY_CORE_ASSERT(false, "Unknow RendererAPI");
        return nullptr;
    }

    Shader* Shader::Create(const std::string vertex, const std::string fragment)
    {

        switch(Renderer::GetAPI()){

            case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertex, fragment);

        }


        STUDY_CORE_ASSERT(false, "Unknow RendererAPI");
        return nullptr;
    }

}