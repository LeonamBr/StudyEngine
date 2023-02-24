#include "SandBox2D.h"
#include "../StudyEngine/src/Engine/Core/EntryPoint.h"
#include <glm/gtc/type_ptr.hpp>


SandBox2D::SandBox2D() : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandBox2D::OnAttach()
{

    STUDY_PROFILE_FUNCTION();
    
    Study::ImGUIRenderer::Init();
    m_ImGui.reset(Study::ImGUIRenderer::Get());
    m_Texture = Study::Texture2D::Create("../Assets/2DTextures/testImage.png");
    m_Ghost = Study::Texture2D::Create("../Assets/2DTextures/testImage1.png");
    m_Background = Study::Texture2D::Create("../Assets/2DTextures/BlackWhiteBoard.png");

}

void SandBox2D::OnDetach()
{
    
    STUDY_PROFILE_FUNCTION();

}

void SandBox2D::OnUpdate(Study::Timer timestep)
{

    STUDY_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(timestep);

    Study::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Study::RendererCommand::Clear();

    Study::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Study::Renderer2D::DrawQuad({-0.5f, 0.0f,  0.0f}, {0.1f, 0.1f}, {0.0f, 0.0f, 1.0f, 1.0f});
    Study::Renderer2D::DrawQuad({-0.45f, 0.05f, -0.1f}, {0.1f, 0.1f}, {1.0f, 0.0f, 0.0f, 1.0f});
   
    //Study::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {100.0f, 100.0f}, m_Background, 100.0f, glm::vec4({0.9f, 0.3f, 1.0f, 0.3f}));
    //Study::Renderer2D::DrawRotatedQuad({0.0, -0.8f}, {1.0f, 1.0f}, glm::radians(90.0f), m_Texture);
    //Study::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_Ghost);
    
    Study::Renderer2D::EndScene();


}

void SandBox2D::OnImGuiRender()
{

    //m_ImGui->Begin("Settings");
    //m_ImGui->ColorEdit4("Triangle Color", glm::value_ptr(m_SquareColor));
    //m_ImGui->End();

}

void SandBox2D::OnEvent(Study::Event &e)
{
    STUDY_PROFILE_FUNCTION();
    m_CameraController.OnEvent(e);

}
