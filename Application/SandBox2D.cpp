#include "SandBox2D.h"
#include "../StudyEngine/include/imGUI/imgui.h"
#include "../StudyEngine/src/Engine/Core/EntryPoint.h"
#include <glm/gtc/type_ptr.hpp>

float SandBox2D::s_FPS = 0.0f;
float SandBox2D::s_Time = 0.0f;

SandBox2D::SandBox2D() : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f)
{
    ImGui::CreateContext();
}

void SandBox2D::OnAttach()
{

    STUDY_PROFILE_FUNCTION();
    
    m_Texture = Study::Texture2D::Create("../Assets/2DTextures/testImage.png");
    m_Ghost = Study::Texture2D::Create("../Assets/2DTextures/testImage1.png");
    m_Background = Study::Texture2D::Create("../Assets/2DTextures/BlackWhiteBoard.png");
    m_Jeff = Study::Texture2D::Create("../Assets/2DTextures/jeff.png");
    m_Marcus = Study::Texture2D::Create("../Assets/2DTextures/marcus.png");
    m_Nicholas = Study::Texture2D::Create("../Assets/2DTextures/nicholas.png");
    m_Sheet = Study::Texture2D::Create("../Assets/2DTextures/Pac-Man_Comparable_Sprite_Sheet.png");

    m_PacmanSheet = Study::SubTexture2D::CreateFromCoords(m_Sheet, {1.0f, 9.0f}, {16.0f, 16.0f});

    m_CameraController.SetZoomLevel(5.0f);

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

    static float tsrotation = 0.0f;
    tsrotation += timestep*50.0f;

    Study::Renderer2D::ResetStats();

    Study::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Study::RendererCommand::Clear();

    Study::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Study::Renderer2D::DrawRotatedQuad({-0.5f, 0.0f,  0.0f}, {0.1f, 0.1f}, -tsrotation, {0.0f, 0.0f, 1.0f, 1.0f});
    Study::Renderer2D::DrawRotatedQuad({-0.45f, 0.05f, -0.1f}, {0.1f, 0.1f}, tsrotation, {1.0f, 0.0f, 0.0f, 1.0f});
   
    Study::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {100.0f, 100.0f}, m_Background, 100.0f, glm::vec4({0.9f, 0.3f, 1.0f, 0.3f}));
    Study::Renderer2D::DrawRotatedQuad({0.0, -0.8f}, {0.1f, 0.1f}, tsrotation ,m_Texture);
    Study::Renderer2D::DrawRotatedQuad({0.0f, 0.0f}, {0.1f, 0.1f}, -tsrotation, m_Ghost);
    Study::Renderer2D::DrawQuad({0.0f, -0.4f}, {1.0f, 1.0f}, m_PacmanSheet);
    
    Study::Renderer2D::EndScene();


}

void SandBox2D::OnImGuiRender()
{

    ImGui::Begin("Renderer Stats");

    auto stats = Study::Renderer2D::GetStats();

    ImGui::Text("Renderer2D Stats - (Frametime: %.2f ms | FPS: %.2f ) ", s_Time, s_FPS);
    ImGui::Text("DrawCalls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::End();
    
}

void SandBox2D::OnEvent(Study::Event &e)
{
    STUDY_PROFILE_FUNCTION();
    m_CameraController.OnEvent(e);

}
