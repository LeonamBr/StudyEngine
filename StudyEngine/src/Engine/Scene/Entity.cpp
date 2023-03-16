#include "../../Headers.h"

#include "Entity.h"

namespace Study {

    Entity::Entity(entt::entity handle, Scene *scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {
    }

}