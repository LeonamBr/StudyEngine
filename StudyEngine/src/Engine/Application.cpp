#include "../Headers.h"

#include "Application.h"

#include "Event/ApplicationEvent.h"
#include "Log.h"

#include <GLFW/glfw3.h>

namespace Study{

    Application::Application(){
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application(){

    }

    void Application::run(){

        while(m_Running)
        {
            
            m_Window->OnUpdate();
        }

    }

}