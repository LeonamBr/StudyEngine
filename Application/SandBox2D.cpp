#include "SandBox2D.h"
#include "../StudyEngine/include/imGUI/imgui.h"
#include "../StudyEngine/src/Engine/Core/EntryPoint.h"
#include <glm/gtc/type_ptr.hpp>

float SandBox2D::s_FPS = 0.0f;
float SandBox2D::s_Time = 0.0f;

SandBox2D::SandBox2D() : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f)
{
    
}

void SandBox2D::OnAttach()
{

    STUDY_PROFILE_FUNCTION();
    
    ImGui::SetCurrentContext(Study::ImGuiLayer::GetContext());

    Study::FramebufferSpec fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Frame = Study::Framebuffer::Create(fbSpec);

    m_Scene = Study::CreateShared<Study::Scene>();

    auto square = m_Scene->CreateEntity("Red Square");
    square.AddComponents<Study::SpriteRendererComponent>(glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});
    m_Camera = m_Scene->CreateEntity("Camera Entity");
    m_Camera.AddComponents<Study::CameraComponent>();
    m_Entity = m_Scene->CreateEntity("Entity");
    m_Scene->DeleteEntity(m_Entity);

    m_Texture = Study::Texture2D::Create("../Assets/2DTextures/testImage.png");
    m_Ghost = Study::Texture2D::Create("../Assets/2DTextures/testImage1.png");
    m_Background = Study::Texture2D::Create("../Assets/2DTextures/BlackWhiteBoard.png");
    m_Jeff = Study::Texture2D::Create("../Assets/2DTextures/jeff.png");
    m_Marcus = Study::Texture2D::Create("../Assets/2DTextures/marcus.png");
    m_Nicholas = Study::Texture2D::Create("../Assets/2DTextures/nicholas.png");
    m_Sheet = Study::Texture2D::Create("../Assets/2DTextures/Pac-Man_Comparable_Sprite_Sheet.png");
    m_Joao = Study::Texture2D::Create("../Assets/2DTextures/joao.png");


    m_PacmanSheet = Study::SubTexture2D::CreateFromCoords(m_Sheet, {1.0f, 9.0f}, {16.0f, 16.0f});

    class CameraController : public Study::ScriptableEntity 
    {

        public:

            void OnCreate()
            {

            }

            void OnDestroy()
            {

            }

            void OnUpdate(Study::Timer timeStep)
            {

                auto& transform = GetComponent<Study::TransformComponent>().Translation;
                float speed = 5.0f;

                if(Study::Input::IsKeyPressed(STUDY_KEY_A))
                    transform.x -= speed * timeStep;
                if(Study::Input::IsKeyPressed(STUDY_KEY_D))
                    transform.x += speed * timeStep;
                if(Study::Input::IsKeyPressed(STUDY_KEY_W))
                    transform.y += speed * timeStep;
                if(Study::Input::IsKeyPressed(STUDY_KEY_S))
                    transform.y -= speed * timeStep;

            }

    };

    m_Camera.AddComponents<Study::NativeScriptComponent>().Bind<CameraController>();

}

void SandBox2D::OnDetach()
{
    
    STUDY_PROFILE_FUNCTION();

}

void SandBox2D::OnUpdate(Study::Timer timestep)
{

    STUDY_PROFILE_FUNCTION();

    s_Time = timestep * 1000.0f;
    s_FPS = 1.0f/timestep;

    
    m_CameraController.OnUpdate(timestep);
    m_Scene->OnViewportResize(Study::Application::Get().GetWindow().GetWidth(), Study::Application::Get().GetWindow().GetHeight());
    Study::Renderer2D::ResetStats();
    m_Frame->Bind();

    static float tsrotation = 0.0f;
    tsrotation += timestep*50.0f;


    Study::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Study::RendererCommand::Clear();

    m_Scene->OnUpdate(timestep);

    m_Frame->Unbind();


}

void SandBox2D::OnImGuiRender()
{

    if(ImGui::BeginMenuBar())
    {

        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Exit"))
                STUDY_WARN("Cheguei");
        
            ImGui::EndMenu();
        }


        ImGui::EndMenuBar();
    }

    ImGui::ShowDemoWindow();

    ImGui::Begin("Renderer Stats");

    auto stats = Study::Renderer2D::GetStats();

    ImGui::Text("Renderer2D Stats - (Frametime: %.2f ms | FPS: %.2f ) ", s_Time, s_FPS);
    ImGui::Text("DrawCalls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::Text("Window Width: %d  Window Height %d", Study::Application::Get().GetWindow().GetWidth(), Study::Application::Get().GetWindow().GetHeight());

    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");

	m_ViewportFocused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();
	Study::Application::Get().GetImGuiLayer()->SetBlocklEvents(!m_ViewportFocused || !m_ViewportHovered);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

	uint64_t textureID = m_Frame->GetColorAttachmentRendererID();
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
	ImGui::PopStyleVar();

    
}

void SandBox2D::OnEvent(Study::Event &e)
{
    STUDY_PROFILE_FUNCTION();
    m_CameraController.OnEvent(e);

}
