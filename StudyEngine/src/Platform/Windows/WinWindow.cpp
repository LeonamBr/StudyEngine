#include "../../Headers.h"
#include "WinWindow.h"


#include "../../Engine/Event/ApplicationEvent.h"
#include "../../Engine/Event/MouseEvent.h"
#include "../../Engine/Event/KeyEvent.h"

#include "../OpenGL/GLContext.h"


namespace Study{

    static uint8_t s_GLFWCount = 0;

    static void GLFWErrorCallback(int error, const char* description){

        STUDY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);

    }


    Unique<Window> Window::Create(const WindowProps& props){
        

        return CreateUnique<WinWindow>(props);

    }

    WinWindow::WinWindow(const WindowProps& props){

        STUDY_PROFILE_FUNCTION();
        Init(props);

    }

    WinWindow::~WinWindow(){

        STUDY_PROFILE_FUNCTION();

        Shutdown();

    }

    void WinWindow::Init(const WindowProps& props){

        STUDY_PROFILE_FUNCTION();

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;


        STUDY_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if(s_GLFWCount == 0){

            STUDY_PROFILE_SCOPE("glfwInit");

            int success = glfwInit();
            STUDY_CORE_ASSERT(success, "Could not initialize GLFW!!");

            glfwSetErrorCallback(GLFWErrorCallback);

        }

        {
            STUDY_PROFILE_SCOPE("glfwCreateWindow");
            m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
            ++s_GLFWCount;
        }
        
        m_Context = CreateUnique<GLContext>(m_Window);
        m_Context->Init() ;
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){

           WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

           data.Width = width;
           data.Height = height;

           WindowResizeEvent event(width, height);
           data.EventCallback(event);
           
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);

        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){


            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleaseEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }

        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key){

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(key);

            data.EventCallback(event);

        });


        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }

        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);

        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);

        });

    }

    void WinWindow::Shutdown()
	{
        STUDY_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
        --s_GLFWCount;

        if(s_GLFWCount == 0)
        {
            glfwTerminate();
        }
	}

	void WinWindow::OnUpdate()
	{

        STUDY_PROFILE_FUNCTION();

		glfwPollEvents();
        m_Context->SwapBuffers();

	}

	void WinWindow::SetVSync(bool enabled)
	{

        STUDY_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}