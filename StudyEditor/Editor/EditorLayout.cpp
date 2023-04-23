#include "EditorLayout.h"

#include "../../StudyEngine/src/Engine/Renderer/Renderer2D.h"

namespace Study {

    EditorLayout::EditorLayout()
    {
    }

    void EditorLayout::OnAttach()
    {

        m_DockSpace = CreateShared<ImGuiDockSpace>();

        m_DockSpace->OnAttach();

    }

    void EditorLayout::OnImGuiRender()
    {

        if(ImGuiDockSpace::s_DockSpace)
            m_DockSpace->Render();
        
        ImGui::Begin("Render Stats");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        ImGui::End();


    }

}