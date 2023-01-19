#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Event/Event.h"
#include "Window.h"

namespace Study{

    class STUDY_API Application{

        public:
            Application();
            virtual ~Application();

            void run();
        
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;

    };

    Application* CreateApplication();

}


#endif