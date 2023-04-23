#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>

#include "../Core/Timer.h"

#include "EditorCamera.h"


namespace Study {

    class Entity;

    class STUDY_API Scene {

        public:
            Scene();
            ~Scene();

            Entity CreateEntity(const std::string& name = std::string());
            void DeleteEntity(Entity entity);
        
            void OnUpdateRuntime(Timer timestep);
            void OnUpdateEditor(Timer timestep, EditorCamera& camera);
            void OnViewportResize(uint32_t width, uint32_t height);

            Entity GetPrimaryCameraEntity();

        private:

            template<typename T> STUDY_API
            void OnComponentAdded(Entity entity, T& component);

        private:

            entt::registry m_Registry;
            uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
            
            friend class Entity;
            friend class SceneHierarchyPanel;
            friend class SceneSerializer;
            friend class ViewPort;
    };

}

#endif