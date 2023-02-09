#include "../StudyEngine/src/Study.h"

#include "../StudyEngine/src/Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class LayerTest : public Study::Layer{

    public:
        LayerTest() : Layer("Test!"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_TrianglePosition(0.0f) {

            m_VArray.reset(Study::VertexArray::Create());
            Study::ImGUIRenderer::Init();
            m_ImGui.reset(Study::ImGUIRenderer::Get());

        float vertices[4*5] = {
            -0.1f, -0.1f, 0.0f, 0.0f, 0.0f,
             0.1f, -0.1f, 0.0f, 1.0f, 0.0f,
             0.1f,  0.1f, 0.0f, 1.0f, 1.0f,
            -0.1f,  0.1f, 0.0f, 0.0f, 1.0f,
        };

        m_VBuffer.reset(Study::VertexBuffer::Create(vertices, sizeof(vertices)));

       
        Study::BufferLayout layout = {
            { Study::ShaderDataType::Vec3, "a_Position" },
            { Study::ShaderDataType::Vec2, "a_Texture"}
        };

        m_VBuffer->SetLayout(layout);
        m_VArray->AddVertexBuffer(m_VBuffer);


        uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
        m_IBuffer.reset(Study::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_VArray->AddIndexBuffer(m_IBuffer);

        
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_Texture;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_Texture;

            void main(){
                
                v_Texture = a_Texture;

                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);

            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec2 v_Texture;
            
            uniform sampler2D u_Texture;

            void main(){
                
                color = texture(u_Texture, v_Texture);
    

            }

        )";


        m_Shader.reset(Study::Shader::Create(vertexSrc, fragmentSrc));

        m_Texture = Study::Texture2D::Create("../testImage.png");

        std::dynamic_pointer_cast<Study::OpenGLShader>(m_Shader)->Bind();
        std::dynamic_pointer_cast<Study::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);

        }

        void OnUpdate(Study::Timer timestep) override{


            if(Study::Input::IsKeyPressed(STUDY_KEY_LEFT))
                m_CameraPosition.x -= m_CameraMoveSpeed*timestep;
            else if(Study::Input::IsKeyPressed(STUDY_KEY_RIGHT))
                m_CameraPosition.x += m_CameraMoveSpeed*timestep;

            if(Study::Input::IsKeyPressed(STUDY_KEY_UP))
                m_CameraPosition.y += m_CameraMoveSpeed*timestep;
            else if(Study::Input::IsKeyPressed(STUDY_KEY_DOWN))
                m_CameraPosition.y -= m_CameraMoveSpeed*timestep;

            if(Study::Input::IsKeyPressed(STUDY_KEY_A))
                m_CameraRotation += m_CameraRotationMoveSpeed*timestep;
            if(Study::Input::IsKeyPressed(STUDY_KEY_D))
                m_CameraRotation -= m_CameraRotationMoveSpeed*timestep;
            if(Study::Input::IsKeyPressed(STUDY_KEY_S)){
                m_CameraPosition.x = 0.0f;
                m_CameraPosition.y = 0.0f; 
                m_CameraRotation = 0.0f;
                m_TrianglePosition.x = 0.0f;
                m_TrianglePosition.y = 0.0f;
                }  

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

            m_Camera.SetPosition(m_CameraPosition);
            m_Camera.SetRotation(m_CameraRotation);
            
            Study::Renderer::BeginScene(m_Camera);

            std::dynamic_pointer_cast<Study::OpenGLShader>(m_Shader)->Bind();
            std::dynamic_pointer_cast<Study::OpenGLShader>(m_Shader)->UploadUniformVec3("u_Color", m_PinkColor);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);

            
            m_Texture->Bind();
            Study::Renderer::Submit(m_Shader, m_VArray, transform);
            Study::Renderer::EndScene();
            
        }

        virtual void OnImGuiRender() override{

           //m_ImGui->Begin("Settings");
           //m_ImGui->ColorEdit3("Triangle Color", glm::value_ptr(m_PinkColor));
           //m_ImGui->End();
 
        }

        void OnEvent(Study::Event& event) override{

           
        }
    
    private:

        Study::Shared<Study::Shader> m_Shader;
        Study::Shared<Study::VertexBuffer> m_VBuffer;
        Study::Shared<Study::IndexBuffer> m_IBuffer;
        Study::Shared<Study::VertexArray> m_VArray;
        Study::Shared<Study::ImGUIRenderer> m_ImGui;
        Study::Shared<Study::Texture2D> m_Texture;

        Study::OrthographicCamera m_Camera;
        glm::vec3 m_CameraPosition;

        float m_CameraMoveSpeed = 2.5f;
        float m_CameraRotation = 0.0f;
        float m_CameraRotationMoveSpeed = 180.0f;

        glm::vec3 m_TrianglePosition;
        float m_TriangleMoveSpeed = 0.5f;
        glm::vec3 m_PinkColor = {0.8f, 0.0f, 0.8f};

};

class TestAPI : public Study::Application{

    public:
        TestAPI(){

            PushLayer(new LayerTest());

        }
        ~TestAPI(){}

};

Study::Application* Study::CreateApplication(){

    return new TestAPI();
}