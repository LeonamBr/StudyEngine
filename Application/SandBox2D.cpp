#include "SandBox2D.h"
#include "../StudyEngine/src/Engine/Core/EntryPoint.h"
#include <glm/gtc/type_ptr.hpp>

#include "../StudyEngine/src/Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D() : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandBox2D::OnAttach()
{
    Study::ImGUIRenderer::Init();
    m_ImGui.reset(Study::ImGUIRenderer::Get());
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Study::Timer timestep)
{
    m_CameraController.OnUpdate(timestep);

    Study::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Study::RendererCommand::Clear();

    Study::Renderer2D::BeginScene(m_CameraController.GetCamera());
        
    Study::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.2f, 1.0f});

    Study::Renderer2D::EndScene();

    //std::dynamic_pointer_cast<Study::OpenGLShader>(m_Shader)->UploadUniformVec4("u_Color", m_SquareColor);
    //std::dynamic_pointer_cast<Study::OpenGLShader>(m_Shader)->Bind();

}

void SandBox2D::OnImGuiRender()
{

    m_ImGui->Begin("Settings");
    m_ImGui->ColorEdit4("Triangle Color", glm::value_ptr(m_SquareColor));
    m_ImGui->End();

}

void SandBox2D::OnEvent(Study::Event &e)
{
    
    m_CameraController.OnEvent(e);

}
