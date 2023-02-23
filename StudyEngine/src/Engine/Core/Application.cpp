#include "../../Headers.h"

#include "Application.h"
#include "Log.h"

#include <GLAD/glad/glad.h>

#include "../Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>


namespace Study{

    Application* Application::s_Instance = nullptr;

    Application::Application(){

        STUDY_PROFILE_FUNCTION();

        STUDY_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(STUDY_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
	    PushOverlay(m_ImGuiLayer);

    }

    Application::~Application()
    {

        STUDY_PROFILE_FUNCTION();

        Renderer::Shutdown();

    }

    void Application::PushLayer(Layer* layer){

        STUDY_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();

    }

    void Application::PushOverlay(Layer* overlay){

        STUDY_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();

    }

    void Application::OnEvent(Event& e){

        STUDY_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(STUDY_BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(STUDY_BIND_EVENT_FN(OnWindowResize));


        for(auto it = m_LayerStack.end(); it!= m_LayerStack.begin(); ){

            (*--it)->OnEvent(e);
            if(e.m_Handled)
                break;

        }

    }


    void Application::run(){

        STUDY_PROFILE_FUNCTION();

        while(m_Running)
        {

            STUDY_PROFILE_SCOPE("GameLoop");

            float time = (float)glfwGetTime();
            Timer timestep = time - m_LastTime;
            m_LastTime = time;

            if(!m_Minimized)
            {
                {

                    STUDY_PROFILE_SCOPE("LAyerStack OnUpdate");

                    for (Layer* layer : m_LayerStack)
                        layer->OnUpdate(timestep);

                }
                m_ImGuiLayer->Begin();

                {

                    STUDY_PROFILE_SCOPE("LAyerStack ImGuiRender");

                    for (Layer* layer : m_LayerStack)
                        layer->OnImGuiRender();

                }
                    m_ImGuiLayer->End();
            }


            m_Window->OnUpdate();
        }

    }

    bool Application::OnWindowClose(WindowCloseEvent& e){


        m_Running = false;
        return true;
        
    }

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        STUDY_PROFILE_FUNCTION();

        if(e.GetWidth() == 0 || e.GetHeight() == 0){
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
}