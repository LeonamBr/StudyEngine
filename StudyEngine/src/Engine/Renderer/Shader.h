#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Study{

    class STUDY_API Shader {
        public:

            ~Shader() = default;

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual void SetInt(const std::string &name, int Int)  = 0;
            virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
            virtual void SetFloat(const std::string &name, float Float)  = 0;
            virtual void SetVec2(const std::string &name, const glm::vec2& vec)  = 0;
            virtual void SetVec3(const std::string &name, const glm::vec3& vec)  = 0;
            virtual void SetVec4(const std::string &name, const glm::vec4& vec)  = 0;
            virtual void SetMat4(const std::string &name, const glm::mat4& mat)  = 0;

            virtual const std::string& GetName() const = 0;

            static Shared<Shader> Create(const std::string& path);
            static Shared<Shader> Create(const std::string& name, const std::string& vertex, const std::string& fragment);

    };

    class STUDY_API ShaderLibrary {

        public:
            void Add(const Shared<Shader>& shader);
            void Add(const std::string& name, const Shared<Shader>& shader);
            Shared<Shader> Load(const std::string& path);
            Shared<Shader> Load(const std::string& name, const std::string& path);

            Shared<Shader> Get(const std::string& name);
        
        private:
            bool Exists(const std::string& name) const;

        private:
            std::unordered_map<std::string, Shared<Shader>> m_Shaders;

    };

} 

#endif