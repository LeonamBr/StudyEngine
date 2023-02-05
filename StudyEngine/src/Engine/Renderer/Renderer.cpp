#include "../../Headers.h"

#include "Renderer.h"

namespace Study {

    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray)
    {

        vertexArray->Bind();
        RendererCommand::DrawIndex(vertexArray);

    }
}