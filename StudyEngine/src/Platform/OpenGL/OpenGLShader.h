#ifndef OPENGLSHADERSHADER_H
#define OPENGLSHADERSHADER_H

#include "../../Engine/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Study{

    class OpenGLShader : public Shader {
        
        public:

            OpenGLShader(const std::string& path);
            OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment);
            virtual ~OpenGLShader();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void SetInt(const std::string &name, int Int) override;
            virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
            virtual void SetFloat(const std::string& name, float Float) override;

            virtual void SetVec2(const std::string &name, const glm::vec2& vec) override;
            virtual void SetVec3(const std::string &name, const glm::vec3& vec) override;
            virtual void SetVec4(const std::string &name, const glm::vec4& vec) override;
            virtual void SetMat4(const std::string &name, const glm::mat4& mat) override;

            virtual const std::string& GetName() const override { return m_Name; }

            void UploadUniformInt(const std::string& name, int value);
            void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

            void UploadUniformfloat(const std::string& name, float value);
            void UploadUniformVec2(const std::string& name, const glm::vec2& value);
            void UploadUniformVec3(const std::string& name, const glm::vec3& value);
            void UploadUniformVec4(const std::string& name, const glm::vec4& value);

            void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
            void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        private:

            std::string ReadFile(const std::string& path);
            std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
            void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        private:

            uint32_t m_RendererID;
            std::string m_Name;

    };

}

#endif