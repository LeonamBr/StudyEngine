#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace Study{

    class STUDY_API Shader {
        public:

            Shader(const std::string vertex, const std::string fragment);
            ~Shader();

            void Bind() const;
            void Unbind() const;

        private:

            uint32_t m_RendererID;

    };

}




#endif