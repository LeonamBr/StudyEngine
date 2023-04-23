#ifndef ENTITY_H
#define ENTITY_H

#include<entt/entt.hpp>


#include "Scene.h"

namespace Study {

    class STUDY_API Entity {

        public: 
            Entity() = default;
            Entity(entt::entity handle, Scene* scene);
            Entity(const Entity& other) = default;

            template<typename T, typename... Args>
            T& AddComponents(Args&&... args)
            {
                STUDY_CORE_ASSERT(!HasComponent<T>(), "Entity alread has component!");

                T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
                m_Scene->OnComponentAdded<T>(*this, component);

                return component;
            }


            template<typename T>
            T& GetComponent()
            {
                
                STUDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have componenty!");
                return m_Scene->m_Registry.get<T>(m_EntityHandle);
            }
            
            template<typename T>
            bool HasComponent()
            {
                return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
            }

            template<typename T>
            void RemoveComponent()
            {
                STUDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have componenty!");

                m_Scene->m_Registry.remove<T>(m_EntityHandle);
            }

            operator bool() const { return m_EntityHandle != entt::null; }
            operator entt::entity() const { return m_EntityHandle; }
            operator uint32_t() const { return (uint32_t)m_EntityHandle; }

            bool operator==(const Entity& other) const 
            {
                return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
            }

            bool operator!=(const Entity& other)
            {
                return !(*this == other);
            }

        private:

            entt::entity m_EntityHandle { entt::null };
            Scene* m_Scene = nullptr;

    };

}

#endif