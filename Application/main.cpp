#include "../StudyEngine/src/Study.h"

#include "SandBox2D.h"

#include "../StudyEngine/src/Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class LayerTest : public Study::Layer{

    public:
        LayerTest() : Layer("Test!"), m_CameraController(1280.0f / 720.0f), m_TrianglePosition(0.0f) {

            m_VArray = Study::VertexArray::Create();
            Study::ImGUIRenderer::Init();
            m_ImGui.reset(Study::ImGUIRenderer::Get());

        float vertices[4*5] = {
            -0.1f, -0.1f, 0.0f, 0.0f, 0.0f,
             0.1f, -0.1f, 0.0f, 1.0f, 0.0f,
             0.1f,  0.1f, 0.0f, 1.0f, 1.0f,
            -0.1f,  0.1f, 0.0f, 0.0f, 1.0f,
        };

        m_VBuffer = Study::VertexBuffer::Create(vertices, sizeof(vertices));

       
        Study::BufferLayout layout = {
            { Study::ShaderDataType::Vec3, "a_Position" },
            { Study::ShaderDataType::Vec2, "a_Texture"}
        };

        m_VBuffer->SetLayout(layout);
        m_VArray->AddVertexBuffer(m_VBuffer);


        uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
        m_IBuffer = Study::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));
        m_VArray->AddIndexBuffer(m_IBuffer);

        //m_Shader = Study::Shader::Create("../Assets/Shaders/texShader.glsl");

        auto textureShader = m_ShaderLibrary.Load("../Assets/Shaders/texShader.glsl");

        m_Texture = Study::Texture2D::Create("../Assets/2DTextures/testImage.png");

        std::dynamic_pointer_cast<Study::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<Study::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

        }

        void OnUpdate(Study::Timer timestep) override{

            m_CameraController.OnUpdate(timestep);

             if(Study::Input::IsKeyPressed(STUDY_KEY_J))
                m_TrianglePosition.x -= m_TriangleMoveSpeed*timestep;
            else if(Study::Input::IsKeyPressed(STUDY_KEY_L))
                m_TrianglePosition.x += m_TriangleMoveSpeed*timestep;
            if(Study::Input::IsKeyPressed(STUDY_KEY_I))
                m_TrianglePosition.y += m_TriangleMoveSpeed*timestep;
            else if(Study::Input::IsKeyPressed(STUDY_KEY_K))
                m_TrianglePosition.y -= m_TriangleMoveSpeed*timestep;

            Study::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
			Study::RendererCommand::Clear();
            
            Study::Renderer::BeginScene(m_CameraController.GetCamera());

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);

            auto textureShader = m_ShaderLibrary.Get("texShader");
            m_Texture->Bind();
            Study::Renderer::Submit(textureShader, m_VArray, transform);
            Study::Renderer::EndScene();
            
        }

        virtual void OnImGuiRender() override{

           //m_ImGui->Begin("Settings");
           //m_ImGui->ColorEdit3("Triangle Color", glm::value_ptr(m_PinkColor));
           //m_ImGui->End();
 
        }

        void OnEvent(Study::Event& event) override{

            m_CameraController.OnEvent(event);
           
        }
    
    private:

        Study::ShaderLibrary m_ShaderLibrary;
        Study::Shared<Study::Shader> m_Shader;
        Study::Shared<Study::VertexBuffer> m_VBuffer;
        Study::Shared<Study::IndexBuffer> m_IBuffer;
        Study::Shared<Study::VertexArray> m_VArray;
        Study::Shared<Study::ImGUIRenderer> m_ImGui;
        Study::Shared<Study::Texture2D> m_Texture;

        Study::OrthographicCameraController m_CameraController;

        glm::vec3 m_TrianglePosition;
        float m_TriangleMoveSpeed = 0.5f;
        //glm::vec3 m_PinkColor = {0.8f, 0.0f, 0.8f};

};

class TestAPI : public Study::Application{

    public:
        TestAPI(){

            //PushLayer(new LayerTest());
            PushLayer(new SandBox2D());

        }
        ~TestAPI(){}

};

Study::Application* Study::CreateApplication(){

    return new TestAPI();
}