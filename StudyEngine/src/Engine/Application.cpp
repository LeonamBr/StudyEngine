#include "../Headers.h"

#include "Application.h"
#include "Log.h"

#include <GLFW/glfw3.h>

namespace Study{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application(){
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application(){

    }

    void Application::OnEvent(Event& e){

        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        STUDY_CORE_TRACE("{0}", e);

    }


    void Application::run(){

        while(m_Running)
        {
            
            m_Window->OnUpdate();
        }

    }

    bool Application::OnWindowClose(WindowCloseEvent& e){

        m_Running = false;
        return true;
        
    }

}