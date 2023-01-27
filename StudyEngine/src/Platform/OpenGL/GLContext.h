#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "../../Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Study {

    class GLContext : public GraphicsContext {

        public:

            GLContext(GLFWwindow* window);
            ~GLContext(){

            }

            virtual void Init() override;
            virtual void SwapBuffers() override;

        private:

            GLFWwindow* m_Window;



    };

}

#endif