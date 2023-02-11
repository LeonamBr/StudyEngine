#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

namespace Study{

    class STUDY_API Shader {
        public:

            ~Shader() = default;

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

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