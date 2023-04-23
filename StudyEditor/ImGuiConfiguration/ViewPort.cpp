#include "ViewPort.h"

#include "../../StudyEngine/include/imGUI/imgui.h"
#include "../../StudyEngine/src/Engine/imGui/ImGuiLayer.h"

#include "../../StudyEngine/include/ImGuizmo/ImGuizmo.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../StudyEngine/src/Engine/Math/Math.h"
#include <initializer_list>

namespace Study{

    ViewPort::ViewPort()
    {
    }

    void ViewPort::OnAttach(Shared<SceneHierarchyPanel>& hierarchyPanel)
    {

        ImGui::SetCurrentContext(ImGuiLayer::GetContext());
        FramebufferSpec m_Spec;
        m_Spec.Attachments = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::Depth};
        m_Spec.Width = 1280;
        m_Spec.Height = 720;

        m_FrameBuffer = Framebuffer::Create(m_Spec);
        m_HierarchyPanel = hierarchyPanel;
        m_HierarchyPanel->OnAttach();

        m_EditorCamera = EditorCamera(30.f, 1.778f, 0.1f, 1000.0f);
        
    }

    void ViewPort::OnUpdate(Timer timeStep)
    {


        if (FramebufferSpec spec = m_FrameBuffer->GetSpecification();
                m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
                (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {

            m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

            m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
            m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

        }

        m_EditorCamera.OnUpdate(timeStep);

    }

    void ViewPort::SetScene(const Shared<Scene> &Scene)
    {
        m_Scene = Scene;
    }

    void ViewPort::Bind()
    {
        m_FrameBuffer->Bind();
    }

    void ViewPort::UnBind()
    {
        m_FrameBuffer->Unbind();
    }

    void ViewPort::OnImGuiRender()
    {


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
        auto viewportOffset = ImGui::GetCursorPos();

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlocklEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();

		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        auto windowSize = ImGui::GetWindowSize();
        ImVec2 minBound = ImGui::GetWindowPos();
        minBound.x += viewportOffset.x;
        minBound.y += viewportOffset.y;

        ImVec2 maxBound = {minBound.x + windowSize.x, minBound.y + windowSize.y};

        m_ViewportBounds[0] = {minBound.x, minBound.y};
        m_ViewportBounds[1] = {maxBound.x, maxBound.y};

        m_HierarchyPanel->OnImGuiRender();


        Entity selectedEntity = m_HierarchyPanel->GetSelectedEntity();
        if(selectedEntity && m_GizmoType !=-1)
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            float windowWidth = ImGui::GetWindowWidth();
            float windowHeight = ImGui::GetWindowHeight();

            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

            const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
            glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

            auto& transformComponent = selectedEntity.GetComponent<TransformComponent>();
            glm::mat4 transform = transformComponent.GetTransform();

            bool snap = Input::IsKeyPressed(STUDY_KEY_LEFT_CONTROL);
            float snapValue = 0.5f;

            if( m_GizmoType == ImGuizmo::OPERATION::ROTATE)
                snapValue = 45.0f;

            float snapValues[3] = { snapValue, snapValue, snapValue};

            ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                (ImGuizmo::OPERATION)m_GizmoType , ImGuizmo::LOCAL, glm::value_ptr(transform),
                nullptr, snap ? snapValues : nullptr);

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 translation, rotation, scale;
                Math::DecomposeTransform(transform, translation, rotation, scale);

                glm::vec3 deltaRotation = rotation - transformComponent.Rotation; 
                transformComponent.Translation = translation;
                transformComponent.Rotation += deltaRotation;
                transformComponent.Scale = scale;
            }

        }

		ImGui::End();
		ImGui::PopStyleVar();
        
    }
}