#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "Window.h"

namespace Study{

    class STUDY_API Application{

        public:
            Application();
            virtual ~Application();

            void run();

            void OnEvent(Event& e);
        
        private:

            bool OnWindowClose(WindowCloseEvent& e);

            std::unique_ptr<Window> m_Window;
            bool m_Running = true;

    };

    Application* CreateApplication();

}


#endif