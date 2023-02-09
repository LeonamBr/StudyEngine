#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace Study{

    class STUDY_API Shader {
        public:

            ~Shader() = default;

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            static Shader* Create(const std::string vertex, const std::string fragment);

    };

}

#endif