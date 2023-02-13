#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

#include "LayerStack.h"
#include "../Event/Event.h"
#include "../Event/ApplicationEvent.h"

#include "../imGui/ImGuiLayer.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Buffer.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/OrthographicCamera.h"

#include "Timer.h"

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
            bool OnWindowResize(WindowResizeEvent& e);
        
        private:

            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            bool m_Minimized = false;
            LayerStack m_LayerStack;
            float m_LastTime;

        private:
            static Application* s_Instance;

    };

    Application* CreateApplication();

}


#endif