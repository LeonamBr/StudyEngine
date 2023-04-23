#ifndef EDITOR_H
#define EDITOR_H

#include "../../StudyEngine/src/Study.h"

#include "../../StudyEngine/src/Engine/Core/Core.h"

#include "EditorLayout.h"
#include "../ImGuiConfiguration/ViewPort.h"
#include "../Panels/SceneHierarchyPanel.h"
#include "../ImGuiConfiguration/ImGuiMenu.h"


namespace Study {

    class Editor : public Layer {

        public:
            Editor();
            virtual ~Editor() = default;

            virtual void OnAttach() override;
            virtual void OnDetach() override;

            void OnUpdate(Timer timestep) override;
            virtual void OnImGuiRender() override;
            void OnEvent(Event& e) override;

        private:
            void RecreateScene();
            void LoadScene();
            void SaveScene();

            bool OnKeyPressed(KeyPressedEvent& e);
        
        private:

            Shared<Scene> m_Scene;
            Shared<EditorLayout> m_Layout;
            Shared<ViewPort> m_ViewPort;
            Shared<ImGuiMenu> m_Menu;
            Shared<SceneHierarchyPanel> m_HierarchyPanel;
            SerializerState m_State;

            static float s_FPS;
            static float s_Time;

    };

}

#endif