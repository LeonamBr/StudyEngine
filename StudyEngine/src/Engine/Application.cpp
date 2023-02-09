#include "../Headers.h"

#include "Application.h"
#include "Log.h"

#include <GLAD/glad/glad.h>

#include "Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>


namespace Study{

    Application* Application::s_Instance = nullptr;

    Application::Application(){

        STUDY_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(STUDY_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
	    PushOverlay(m_ImGuiLayer);

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

            float time = (float)glfwGetTime();
            Timer timestep = time - m_LastTime;
            m_LastTime = time;

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(timestep);

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