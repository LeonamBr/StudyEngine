#include "../../Headers.h"

#include "Renderer.h"

#include "../../Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace Study {

    Unique<Renderer::SceneData> Renderer::s_SceneData =  CreateUnique<Renderer::SceneData>();

    void Renderer::Init()
    {

        STUDY_PROFILE_FUNCTION();

        RendererCommand::Init();
        Renderer2D::Init();

    }

    void Renderer::Shutdown()
    {

        Renderer2D::Shutdown();

    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {

        STUDY_PROFILE_FUNCTION();

        RendererCommand::SetViewport(0, 0, width, height);

    }

    void Renderer::BeginScene(OrthographicCamera &camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Shared<Shader>& shader, const Shared<VertexArray> &vertexArray, const glm::mat4& transform)
    {

        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RendererCommand::DrawIndex(vertexArray);

    }
}