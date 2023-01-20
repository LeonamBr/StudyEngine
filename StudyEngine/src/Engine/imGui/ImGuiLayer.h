#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "../Layer.h"
#include "../../Platform/OpenGL/GlRender.h"

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

            float m_Time = 0.0f;


    };

}


#endif