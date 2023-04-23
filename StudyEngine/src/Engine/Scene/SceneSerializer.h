#ifndef SCENESERIALIZER_H
#define SCENESERIALIZER_H

#include "Scene.h"

namespace Study {

    class STUDY_API SceneSerializer {

        public:
            SceneSerializer(const Shared<Scene>& scene);

            void Serialize(const std::string& filepath);
            void SerializeRuntime(const std::string& filepath);

            bool Deserialize(const std::string& filepath);
            bool DeserializeRuntime(const std::string& filepath);

        private:
            Shared<Scene> m_Scene;

    };

}

#endif