#include "../Headers.h"

#include "Application.h"
#include "Log.h"

#include <GLAD/glad/glad.h>

#include "Input.h"

namespace Study{

    Application* Application::s_Instance = nullptr;

    Application::Application(){

        STUDY_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(STUDY_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
	    PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VArray);
        glBindVertexArray(m_VArray);


        float vertices[3*3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        m_VBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

        uint32_t indices[3] = {0, 1, 2};
        m_IBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

        
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            void main(){
                
                gl_Position = vec4(a_Position, 1.0);

            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 a_Color;

            void main(){
                
                a_Color = vec4(0.8,0.2,0.3,1.0);

            }

        )";


        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

    }

    Application::~Application(){

    }

    void Application::PushLayer(Layer* layer){

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();

    }

    void Application::PushOverlay(Layer* overlay){

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();

    }

    void Application::OnEvent(Event& e){

        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(STUDY_BIND_EVENT_FN(Application::OnWindowClose));


        for(auto it = m_LayerStack.end(); it!= m_LayerStack.begin(); ){

            (*--it)->OnEvent(e);
            if(e.m_Handled)
                break;

        }

    }


    void Application::run(){

        while(m_Running)
        {

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VArray);
            glDrawElements(GL_TRIANGLES, m_IBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


            m_Window->OnUpdate();
        }

    }

    bool Application::OnWindowClose(WindowCloseEvent& e){

        m_Running = false;
        return true;
        
    }

}