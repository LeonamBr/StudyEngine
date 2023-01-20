#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "../Core.h"

#include "../Layer.h"
#include "../../Platform/OpenGL/GlRender.h"

#include "../Event/ApplicationEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"

namespace Study {

    class STUDY_API ImGuiLayer : public Layer{

        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void OnAttach();
            void OnDetach();
            void OnUpdate();
            void OnEvent(Event& event);

        private:

            bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
            bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
            bool OnMouseMovedEvent(MouseMovedEvent& e);
            bool OnMouseScrolledEvent(MouseScrolledEvent& e);
            bool OnKeyPressedEvent(KeyPressedEvent& e);
            bool OnKeyReleaseEvent(KeyReleaseEvent& e);
            bool OnKeyTypedEvent(KeyTypedEvent& e);
            bool OnWindowResizeEvent(WindowResizeEvent& e);

        private:

            float m_Time = 0.0f;


    };

}


#endif