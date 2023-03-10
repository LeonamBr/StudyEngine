#include "../../Headers.h"

#include "OpenGLShader.h"
#include <GLAD/glad/glad.h>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace Study {

    static GLenum ShaderTypeFromString(const std::string& type)
    {

        if(type == "vertex") return GL_VERTEX_SHADER;
        if(type == "fragment" || "pixel") return GL_FRAGMENT_SHADER;

        STUDY_CORE_ASSERT(false, "Unknown shader type");
        return 0;

    }

    OpenGLShader::OpenGLShader(const std::string& path)
    {

        STUDY_PROFILE_FUNCTION();

        std::string source = ReadFile(path);
        auto shaderSources = PreProcess(source);

        Compile(shaderSources);

        auto lastSlash = path.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = path.find_last_of('.');
        
        auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;

        m_Name = path.substr(lastSlash, count);

    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment) : m_Name(name) {
    
        STUDY_PROFILE_FUNCTION();
        
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertex;
        sources[GL_FRAGMENT_SHADER] = fragment;
        Compile(sources);
       
    }

    OpenGLShader::~OpenGLShader()
    {
        STUDY_PROFILE_FUNCTION();

        glDeleteProgram(m_RendererID);

    }
    void OpenGLShader::Bind() const
    {
        STUDY_PROFILE_FUNCTION();

        glUseProgram(m_RendererID);

    }
    void OpenGLShader::Unbind() const
    {

        STUDY_PROFILE_FUNCTION();

        glUseProgram(0);

    }

    void OpenGLShader::SetInt(const std::string &name, int  Int)
    {
        STUDY_PROFILE_FUNCTION();

        UploadUniformInt(name, Int);
    }

    void OpenGLShader::SetIntArray(const std::string &name, int *values, uint32_t count)
    {
        UploadUniformIntArray(name, values ,count);
    }

    void OpenGLShader::SetFloat(const std::string& name, float Float)
    {
        STUDY_PROFILE_FUNCTION();
        UploadUniformfloat(name, Float);
    }

    void OpenGLShader::SetVec2(const std::string &name, const glm::vec2 &vec)
    {
        STUDY_PROFILE_FUNCTION();
        UploadUniformVec2(name, vec);
    }

    void OpenGLShader::SetVec3(const std::string &name, const glm::vec3 &vec)
    {
        STUDY_PROFILE_FUNCTION();
        UploadUniformVec3(name, vec);
    }

    void OpenGLShader::SetVec4(const std::string &name, const glm::vec4 &vec) 
    {
        STUDY_PROFILE_FUNCTION();
        UploadUniformVec4(name, vec);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &mat) 
    {
        STUDY_PROFILE_FUNCTION();
        UploadUniformMat4(name, mat);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformIntArray(const std::string &name, int *values, uint32_t count)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, count, values);
    }

    void OpenGLShader::UploadUniformfloat(const std::string &name, float value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformVec2(const std::string &name, const glm::vec2 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformVec3(const std::string &name, const glm::vec3 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformVec4(const std::string &name, const glm::vec4 &value)
    {
         GLint location = glGetUniformLocation(m_RendererID, name.c_str());
         glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

    }

    void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4& matrix)
    {

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

    }
    std::string OpenGLShader::ReadFile(const std::string &path)
    {

        STUDY_PROFILE_FUNCTION();

        std::string shadertxt;
        std::ifstream in(path, std::ios::in | std::ios::binary);
        if(in)
        {
            in.seekg(0, std::ios::end);
            shadertxt.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&shadertxt[0], shadertxt.size()); 
            in.close();           
        }
        else
        {
            STUDY_CORE_ERROR("Could not open file '{0}", path);
        }

        return shadertxt;
    }
    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {

        STUDY_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSource;

        const char* token = "#type";
        size_t tokenLength = strlen(token);
        size_t position = source.find(token, 0);

        while(position != std::string::npos)
        {

            size_t eol = source.find_first_of("\r\n", position);
            STUDY_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = position + tokenLength + 1;
            std::string type = source.substr(begin,  eol - begin);
            STUDY_CORE_ASSERT( ShaderTypeFromString(type), "Invalid shader type!");

            size_t nextLinePosition = source.find_first_not_of("\r\n", eol);
            STUDY_CORE_ASSERT(nextLinePosition != std::string::npos, "Sintax error");
            position = source.find(token, nextLinePosition);
            shaderSource[ShaderTypeFromString(type)] = (position == std::string::npos) ? source.substr(nextLinePosition) : source.substr(nextLinePosition, position - nextLinePosition);

        }

        return shaderSource;

    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {

        STUDY_PROFILE_FUNCTION();

        GLuint program = glCreateProgram();

        STUDY_CORE_ASSERT(shaderSources.size() <= 2, "Only two shaders are suported at moment");

        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;

        for(auto& keyvalue : shaderSources){
            GLenum type = keyvalue.first;
            const std::string& source = keyvalue.second;

            GLuint shader = glCreateShader(type);

            const GLchar* p_Source = source.c_str();
            glShaderSource(shader, 1, &p_Source, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

            if(isCompiled == GL_FALSE){

                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);

                glDeleteShader(shader);

                STUDY_CORE_ERROR("{0}", infoLog.data());
                STUDY_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }
        
            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;

        }


        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteProgram(program);

            for(auto id: glShaderIDs )
               glDeleteShader(id);
            
            STUDY_CORE_ERROR("{0}", infoLog.data());
            STUDY_CORE_ASSERT(false, "Shader link failure!!");
            return;

        }

        for(auto id: glShaderIDs ) {
            glDetachShader(program, id);
            glDeleteShader(id);
        }

       m_RendererID = program;

    }
    
}