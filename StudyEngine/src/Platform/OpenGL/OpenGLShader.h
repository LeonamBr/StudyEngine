#ifndef OPENGLSHADERSHADER_H
#define OPENGLSHADERSHADER_H

#include "../../Engine/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Study{

    class STUDY_API OpenGLShader : public Shader {
        
        public:

            OpenGLShader(const std::string vertex, const std::string fragment);
            virtual ~OpenGLShader();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            void UploadUniformInt(const std::string& name, int value);

            void UploadUniformfloat(const std::string& name, float value);
            void UploadUniformVec2(const std::string& name, const glm::vec2& value);
            void UploadUniformVec3(const std::string& name, const glm::vec3& value);
            void UploadUniformVec4(const std::string& name, const glm::vec4& value);

            void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
            void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        private:

            uint32_t m_RendererID;

    };

}

#endif