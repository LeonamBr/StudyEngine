#include "../../Headers.h"

#include "GLContext.h"

#include <GLAD/glad/glad.h>
#include <GLFW/glfw3.h>

namespace Study {

    GLContext::GLContext(GLFWwindow* window) : m_Window(window){

        STUDY_CORE_ASSERT(window, "Window is null!!");

    }

    void GLContext::Init(){

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        STUDY_CORE_ASSERT(status, "Failed to initialize Glad!");

    }

    void GLContext::SwapBuffers(){

        glfwSwapBuffers(m_Window);

    }





}