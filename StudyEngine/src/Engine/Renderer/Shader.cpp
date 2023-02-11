#include "../../Headers.h"

#include "Shader.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLShader.h"

namespace Study {
    Shared<Shader> Shader::Create(const std::string& path)
    {
        switch(Renderer::GetAPI()){

            case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);

        }


        STUDY_CORE_ASSERT(false, "Unknow RendererAPI");
        return nullptr;
    }

    Shared<Shader> Shader::Create(const std::string& name, const std::string& vertex, const std::string& fragment)
    {

        switch(Renderer::GetAPI()){

            case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertex, fragment);

        }


        STUDY_CORE_ASSERT(false, "Unknow RendererAPI");
        return nullptr;
    }

    void ShaderLibrary::Add(const Shared<Shader>& shader){

        auto& name = shader->GetName();
        Add(name, shader);

    }

    void ShaderLibrary::Add(const std::string &name, const Shared<Shader> &shader)
    {

        STUDY_CORE_ASSERT( !Exists(name), "Shader alread exists!");
        m_Shaders[name] = shader;

    }

    Shared<Shader> ShaderLibrary::Load(const std::string &path){

        auto shader =  Shader::Create(path);
        Add(shader);
        return shader;

    }

    Shared<Shader> ShaderLibrary::Load(const std::string &name, const std::string& path) {

        auto shader =  Shader::Create(path);
        Add(name, shader);
        return shader;

    }

    Shared<Shader> ShaderLibrary::Get(const std::string &name){

        STUDY_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
    
    

}