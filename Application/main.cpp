#include "../StudyEngine/src/Study.h"


class LayerTest : public Study::Layer{

    public:
        LayerTest() : Layer("Test!"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f) {

            m_VArray.reset(Study::VertexArray::Create());

        float vertices[3*7] = {
            -0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        m_VBuffer.reset(Study::VertexBuffer::Create(vertices, sizeof(vertices)));

       
        Study::BufferLayout layout = {
            { Study::ShaderDataType::Vec3, "a_Position" },
            { Study::ShaderDataType::Vec4, "a_Color"}
        };

        m_VBuffer->SetLayout(layout);
        m_VArray->AddVertexBuffer(m_VBuffer);


        uint32_t indices[3] = {0, 1, 2};
        m_IBuffer.reset(Study::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_VArray->AddIndexBuffer(m_IBuffer);

        
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main(){
                
                v_Position = a_Position;
                v_Color = a_Color;

                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 a_Color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main(){
                
                a_Color = vec4(v_Position, 1.0);
                a_Color = v_Color;

            }

        )";


        m_Shader.reset(new Study::Shader(vertexSrc, fragmentSrc));

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
                }  

            Study::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
			Study::RendererCommand::Clear();

            m_Camera.SetPosition(m_CameraPosition);
            m_Camera.SetRotation(m_CameraRotation);
            
            Study::Renderer::BeginScene(m_Camera);
            Study::Renderer::Submit(m_Shader, m_VArray);
            Study::Renderer::EndScene();
            
        }

        virtual void OnImGuiRender() override{

        }

        void OnEvent(Study::Event& event) override{

           
        }
    
    private:

        std::shared_ptr<Study::Shader> m_Shader;
        std::shared_ptr<Study::VertexBuffer> m_VBuffer;
        std::shared_ptr<Study::IndexBuffer> m_IBuffer;
        std::shared_ptr<Study::VertexArray> m_VArray;

        Study::OrthographicCamera m_Camera;
        glm::vec3 m_CameraPosition;

        float m_CameraMoveSpeed = 2.5f;
        float m_CameraRotation = 0.0f;
        float m_CameraRotationMoveSpeed = 180.0f;

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