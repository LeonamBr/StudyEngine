#include "../../Headers.h"

#include "GLContext.h"

#include <GLAD/glad/glad.h>
#include <GLFW/glfw3.h>

namespace Study {

    GLContext::GLContext(GLFWwindow* window) : m_Window(window){

        STUDY_CORE_ASSERT(window, "Window is null!!");

    }

    void GLContext::Init(){

        STUDY_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        STUDY_CORE_ASSERT(status, "Failed to initialize Glad!");
        STUDY_CORE_INFO("OpenGL: ");
        STUDY_CORE_INFO("Vendor: {0}", (char*)glGetString(GL_VENDOR));
        STUDY_CORE_INFO("Renderer: {0}", (char*)glGetString(GL_RENDERER));
        STUDY_CORE_INFO("Version: {0}", (char*)glGetString(GL_VERSION));

    }

    void GLContext::SwapBuffers(){

        STUDY_PROFILE_FUNCTION();

        glfwSwapBuffers(m_Window);

    }





}