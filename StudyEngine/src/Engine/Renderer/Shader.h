#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

namespace Study{

    class STUDY_API Shader {
        public:

            Shader(const std::string vertex, const std::string fragment);
            ~Shader();

            void Bind() const;
            void Unbind() const;

            void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        private:

            uint32_t m_RendererID;

    };

}




#endif