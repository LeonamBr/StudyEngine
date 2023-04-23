#include "ImGuiMenu.h"

#include "ImGuiDockSpace.h"


namespace Study {

    ImGuiMenu::ImGuiMenu()
    {
       
    }

    void ImGuiMenu::OnAttach()
    {

        ImGui::SetCurrentContext(ImGuiLayer::GetContext());

    }

    void ImGuiMenu::SetScene(Shared<Scene>& scene)
    {
        m_Scene = scene;
    }

    void ImGuiMenu::ImGuiTool()
    {
        ImGuiDockSpace::s_DockSpace = !ImGuiDockSpace::s_DockSpace;
    }


    SerializerState ImGuiMenu::Render(Shared<ViewPort>& viewport, Shared<SceneHierarchyPanel>& sceneHierarchyPanel)
    {

        SerializerState state = SerializerState::isRunning;

        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("New", "Ctrl+N"))
                {
                    state = SerializerState::onCreate;                
                }

                if(ImGui::MenuItem("Open", "Ctrl+O"))
                {
                    state = SerializerState::onLoad;
                }

                if(ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
                {
                    state = SerializerState::onSaving;
                }

                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Tools"))
            {
                if(ImGui::MenuItem("DockSpace"))
                {
                    ImGuiTool();
                }
                ImGui::EndMenu();
            }
        ImGui::EndMainMenuBar();
        }

        return state;
        
    }
}