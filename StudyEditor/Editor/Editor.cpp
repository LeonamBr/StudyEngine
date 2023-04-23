#include "Editor.h"

#include "../../StudyEngine/src/Engine/Core/EntryPoint.h"

#include <glm/glm.hpp>

#include "../../StudyEngine/include/ImGuizmo/ImGuizmo.h"


namespace Study {

    float Editor::s_FPS = 0.0f;
    float Editor::s_Time = 0.0f;

    Editor::Editor() : Layer("Editor")
    {


    }

    void Editor::OnAttach()
    {

        STUDY_PROFILE_FUNCTION();

        m_ViewPort = CreateShared<ViewPort>();
        m_Scene = CreateShared<Scene>();
        m_HierarchyPanel = CreateShared<SceneHierarchyPanel>(m_Scene);
        m_ViewPort->OnAttach(m_HierarchyPanel);
        m_Menu = CreateShared<ImGuiMenu>();
        m_Menu->OnAttach();
        
        m_ViewPort->SetScene(m_Scene);
        m_Menu->SetScene(m_Scene);
        m_Layout = CreateShared<EditorLayout>();

        m_Layout->OnAttach();

    }

    void Editor::OnDetach()
    {

        STUDY_PROFILE_FUNCTION();
    }

    void Editor::OnUpdate(Timer timestep)
    {

        STUDY_PROFILE_FUNCTION();

        m_ViewPort->OnUpdate(timestep);

        s_Time = timestep * 1000.0f;
        s_FPS = 1.0f/timestep;

        Renderer2D::ResetStats();
        m_ViewPort->GetFrame()->Bind();

        RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        RendererCommand::Clear();

        m_Scene->OnUpdateEditor(timestep, m_ViewPort->GetEditorCamera());

        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_ViewPort->m_ViewportBounds[0].x;
        my -= m_ViewPort->m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewPort->m_ViewportBounds[1] - m_ViewPort->m_ViewportBounds[0];
        my = viewportSize.y - my;

        int mouseX = (int)mx;
        int mouseY = (int)my;

        if(mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y )
            STUDY_CORE_WARN(" Pixel - {0}" , m_ViewPort->GetFrame()->ReadPixel(1, mouseX, mouseY));
            

        m_ViewPort->GetFrame()->Unbind();

    }

    void Editor::OnImGuiRender()
    {

        STUDY_PROFILE_FUNCTION();

        m_Layout->OnImGuiRender();
        m_ViewPort->OnImGuiRender();

        m_State = m_Menu->Render(m_ViewPort, m_HierarchyPanel);
        if(m_State == SerializerState::onCreate)
            RecreateScene();
        if(m_State == SerializerState::onLoad)
            LoadScene();
        if(m_State == SerializerState::onSaving)
            SaveScene();


    }

    void Editor::OnEvent(Event &e)
    {
        STUDY_PROFILE_FUNCTION();

        m_ViewPort->GetEditorCamera().OnEvent(e);

        EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(STUDY_BIND_EVENT_FN(OnKeyPressed));

    }

    bool Editor::OnKeyPressed(KeyPressedEvent& e){
		
		if (e.GetRepeatCount() > 0)
			return false;
        

		bool control = Input::IsKeyPressed(STUDY_KEY_LEFT_CONTROL) || Input::IsKeyPressed(STUDY_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(STUDY_KEY_LEFT_SHIFT) || Input::IsKeyPressed(STUDY_KEY_RIGHT_SHIFT);
        
		switch (e.GetKeyCode())
		{
			case STUDY_KEY_N:
			{
                
				if (control)
					RecreateScene();
                
				break;
			}
			case STUDY_KEY_O:
			{
				if (control)
					LoadScene();

				break;
			}
			case STUDY_KEY_S:
			{
				if (control && shift)
					SaveScene();

				break;
			}

            case STUDY_KEY_Q:
			{
                
				m_ViewPort->m_GizmoType = -1;
                
				break;
			}
			case STUDY_KEY_W:
			{
				
				m_ViewPort->m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;

				break;
			}
			case STUDY_KEY_E:
			{
				
				m_ViewPort->m_GizmoType = ImGuizmo::OPERATION::ROTATE;

				break;
			}
            case STUDY_KEY_R:
			{
				
				m_ViewPort->m_GizmoType = ImGuizmo::OPERATION::SCALE;

				break;
			}

		}
        return false;
	}

    void Editor::RecreateScene()
    {
        m_Scene = CreateShared<Scene>();
        m_Scene->OnViewportResize((uint32_t)m_ViewPort->m_ViewportSize.x, (uint32_t)m_ViewPort->m_ViewportSize.y);
        m_ViewPort->SetScene(m_Scene);
        m_HierarchyPanel->SetContext(m_Scene);
    }

    void Editor::LoadScene()
    {

        std::string filepath = FileDialogs::OpenFile("Study Scene (*.study)\0*.study\0");
        if(!filepath.empty())
        {
            
            m_Scene = CreateShared<Scene>();
            m_Scene->OnViewportResize((uint32_t)m_ViewPort->m_ViewportSize.x, (uint32_t)m_ViewPort->m_ViewportSize.y);
            m_ViewPort->SetScene(m_Scene);
            m_HierarchyPanel->SetContext(m_Scene);

            SceneSerializer serializer(m_Scene);
            serializer.Deserialize(filepath);
        }


    }

    void Editor::SaveScene()
    {
        std::string filepath = FileDialogs::SaveFile("Study Scene (*.study)\0*.study\0");
        if(!filepath.empty())
        {
            SceneSerializer serializer(m_Scene);
            serializer.Serialize(filepath);
        }
    }
}