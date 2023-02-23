#include "../../Headers.h"

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RendererCommand.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Study {

    struct Renderer2DStorage
    {
        Shared<VertexArray> VertexArray;
        Shared<Shader> TextureShader;
        Shared<Texture2D> WhiteTexture;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Init()
    {

        STUDY_PROFILE_FUNCTION();

        s_Data = new Renderer2DStorage();
    
        s_Data->VertexArray = Study::VertexArray::Create();
    

        float vertices[4*5] = {
            -0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 
             0.1f, -0.1f, 0.0f, 1.0f, 0.0f,
             0.1f,  0.1f, 0.0f, 1.0f, 1.0f,
            -0.1f,  0.1f, 0.0f, 0.0f, 1.0f
        };

        Shared<VertexBuffer> vertexBuffer;

        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

       
        BufferLayout layout = {
            { ShaderDataType::Vec3, "a_Position" },
            { ShaderDataType::Vec2, "a_Texture"}
        };

    vertexBuffer->SetLayout(layout);
    s_Data->VertexArray->AddVertexBuffer(vertexBuffer);

    s_Data->WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));


    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
    Shared<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
    s_Data->VertexArray->AddIndexBuffer(indexBuffer);

    s_Data->TextureShader = Shader::Create("../Assets/Shaders/UniqueShader.glsl");
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetInt("u_Texture", 0);

    }

    void Renderer2D::Shutdown()
    {
        STUDY_PROFILE_FUNCTION();

        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {

        STUDY_PROFILE_FUNCTION();

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

    }

    void Renderer2D::EndScene()
    {
        STUDY_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        
            DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {

        STUDY_PROFILE_FUNCTION();

        s_Data->TextureShader->SetVec4("u_Color", color);
        s_Data->TextureShader->SetFloat("u_Scale", 1.0f);
        s_Data->WhiteTexture->Bind();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}); 
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->VertexArray->Bind();
        RendererCommand::DrawIndex(s_Data->VertexArray);

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {

        DrawQuad({position.x, position.y, 0.0f}, size, texture, texScale, colorize);

    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {

        STUDY_PROFILE_FUNCTION();

        s_Data->TextureShader->SetVec4("u_Color", colorize);
        s_Data->TextureShader->SetFloat("u_Scale", texScale);

        texture->Bind();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}); 
        s_Data->TextureShader->SetMat4("u_Transform", transform);


        s_Data->VertexArray->Bind();
        RendererCommand::DrawIndex(s_Data->VertexArray);


    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {

        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {

        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, texScale, colorize);

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {

        s_Data->TextureShader->SetVec4("u_Color", color);
        s_Data->TextureShader->SetFloat("u_Scale", 1.0f);

        s_Data->WhiteTexture->Bind();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}); 
        s_Data->TextureShader->SetMat4("u_Transform", transform);


        s_Data->VertexArray->Bind();
        RendererCommand::DrawIndex(s_Data->VertexArray);
        

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {

        s_Data->TextureShader->SetVec4("u_Color", colorize);
        s_Data->TextureShader->SetFloat("u_Scale", texScale);

        texture->Bind();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}); 
        s_Data->TextureShader->SetMat4("u_Transform", transform);


        s_Data->VertexArray->Bind();
        RendererCommand::DrawIndex(s_Data->VertexArray);


    }

}