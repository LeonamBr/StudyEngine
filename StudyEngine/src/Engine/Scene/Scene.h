#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>

#include "../Core/Timer.h"

namespace Study {

    class Entity;

    class STUDY_API Scene {

        public:
            Scene();
            ~Scene();

            Entity CreateEntity(const std::string& name = std::string());
        
            void OnUpdate(Timer timestep);

        private:

        entt::registry m_Registry;
        
        friend class Entity;
    };

}


#endif