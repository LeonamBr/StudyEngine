#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "../Core/Core.h"

#include "../Core/Layer.h"

#include "../Event/ApplicationEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"

namespace Study {

    class STUDY_API ImGuiLayer : public Layer{

        public:
            ImGuiLayer();
            ~ImGuiLayer();

           virtual void OnAttach() override;
           virtual void OnDetach() override;
           virtual void OnImGuiRender() override;

           void Begin();
           void End();

        private:

            float m_Time = 0.0f;


    };

}


#endif