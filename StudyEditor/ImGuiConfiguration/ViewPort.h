#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glm/glm.hpp>

#include "../../StudyEngine/src/Engine/Core/Core.h"
#include "../../StudyEngine/src/Study.h"
#include "../Panels/SceneHierarchyPanel.h"

namespace Study {

    class ViewPort {

        public:
            ViewPort();
            ~ViewPort() = default;

            void OnAttach(Shared<SceneHierarchyPanel>& hierarchyPanel);
            void OnUpdate(Timer timeStep);
            Shared<Framebuffer> GetFrame() const { return m_FrameBuffer; }
            void SetScene(const Shared<Scene>& Scene);
            void Bind();
            void UnBind();
            void OnImGuiRender();
            EditorCamera& GetEditorCamera() { return m_EditorCamera; }

        private:

            bool m_ViewportFocused = false, m_ViewportHovered = false;
		    glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
            glm::vec2 m_ViewportBounds[2];

            Shared<Framebuffer> m_FrameBuffer;
            Shared<SceneHierarchyPanel> m_HierarchyPanel;
            Shared<Scene> m_Scene;
            FramebufferSpec m_Spec;
            EditorCamera m_EditorCamera;

            friend class Editor;

            int m_GizmoType = -1;

    };


}

#endif