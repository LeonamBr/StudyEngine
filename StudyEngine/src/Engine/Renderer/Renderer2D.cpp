#include "../../Headers.h"

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RendererCommand.h"

#include "../../Platform/OpenGL/OpenGLShader.h"

namespace Study {

    struct Renderer2DStorage
    {
        Shared<VertexArray> VertexArray;
        Shared<Shader> ColorShader;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Init()
    {

    s_Data = new Renderer2DStorage();
    
    s_Data->VertexArray = Study::VertexArray::Create();
    

        float vertices[3*4] = {
            -0.1f, -0.1f, 0.0f,
             0.1f, -0.1f, 0.0f,
             0.1f,  0.1f, 0.0f,
            -0.1f,  0.1f, 0.0f
        };

        Shared<VertexBuffer> vertexBuffer;

        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

       
        BufferLayout layout = {
            { ShaderDataType::Vec3, "a_Position" }
        };

    vertexBuffer->SetLayout(layout);
    s_Data->VertexArray->AddVertexBuffer(vertexBuffer);


    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
    Shared<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
    s_Data->VertexArray->AddIndexBuffer(indexBuffer);

    s_Data->ColorShader = Shader::Create("../Assets/Shaders/colorShader.glsl");

    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        
            DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {

        std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->UploadUniformVec4("u_Color", color);
        s_Data->VertexArray->Bind();
        RendererCommand::DrawIndex(s_Data->VertexArray);

    }
}