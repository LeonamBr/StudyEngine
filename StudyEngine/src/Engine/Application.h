#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

#include "LayerStack.h"
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

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* overlay);

            inline static Application& Get() { return *s_Instance; }
            inline Window& GetWindow() { return *m_Window; }
        
        private:

            bool OnWindowClose(WindowCloseEvent& e);

            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
            LayerStack m_LayerStack;
        
        private:
            static Application* s_Instance;

    };

    Application* CreateApplication();

}


#endif