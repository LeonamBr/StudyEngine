#include "../../Headers.h"
#include "Scene.h"

#include "Components.h"

#include "../Renderer/Renderer2D.h"

#include "Entity.h"

namespace Study {

    Scene::Scene()
    {

    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        
        Entity entity = { m_Registry.create(), this };
        entity.AddComponents<TransformComponent>();
        auto& tag = entity.AddComponents<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
       

        return entity;
    }

    void Scene::DeleteEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::OnUpdateRuntime(Timer timeStep)
    {

        {
            m_Registry.view<NativeScriptComponent>().each([=, this](auto entity, auto& nsc)
            {
                if(!nsc.Instance)
                {
                    nsc.Instance = nsc.InstantiateFunction();
                    nsc.Instance->m_Entity = Entity{ entity, this};
                    nsc.Instance->OnCreate();
                }

                nsc.Instance->OnUpdate(timeStep);

            });
        }

        Camera* mainCamera = nullptr;
        glm::mat4 cameraTransform;
        
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera.Primary)
                {
                    mainCamera = &camera.Camera;
                    cameraTransform = transform.GetTransform();
                    break;
                }
            }
        }

        if(mainCamera)
        {
            Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);

            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity: group)
            {
                auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

                Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
            }

            Renderer2D::EndScene();

        }

    }

    void Scene::OnUpdateEditor(Timer timestep, EditorCamera& camera)
    {

        Renderer2D::BeginScene(camera);

            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity: group)
            {
                auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

                Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
            }

            Renderer2D::EndScene();

    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {

        m_ViewportWidth = width;
        m_ViewportHeight = height;

        auto view = m_Registry.view<CameraComponent>();
        for ( auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if(!cameraComponent.FixedAspectRatio)
                cameraComponent.Camera.SetViewportSize(width, height);
                
        }

    }

    Entity Scene::GetPrimaryCameraEntity()
    {
       auto view = m_Registry.view<CameraComponent>();
       for (auto& entity: view)
       {
            const auto& camera = view.get<CameraComponent>(entity);
            if(camera.Primary)
            {
                return Entity{entity, this};
            }
       }

       return {};
       
    }

    template <typename T> STUDY_API
    void Scene::OnComponentAdded(Entity entity, T &component)
    {
        static_assert(sizeof(T) == 0, "template needs a especialization");
    }

    template <> STUDY_API
    void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
    {

    }

    template <> STUDY_API
    void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
    }

    template <> STUDY_API
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {

    }

    template <> STUDY_API
    void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
    {

    }

    template <> STUDY_API
    void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {

    }

}