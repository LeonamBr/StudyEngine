#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "../Core/Core.h"

#include "../Core/Layer.h"
#include <imGui/imgui.h>

#include "../Event/ApplicationEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"

namespace Study {

    class STUDY_API ImGuiLayer : public Layer{

        public:
            ImGuiLayer();
            ~ImGuiLayer() = default;

           virtual void OnAttach() override;
           virtual void OnDetach() override;
           virtual void OnEvent(Event& e) override;

           static ImGuiContext* GetContext() { return ImGui::GetCurrentContext(); }

           void Begin();
           void End();

           void SetBlocklEvents(bool block) { m_BlockEvents = block; }

        private:

            bool m_BlockEvents = true;
            float m_Time = 0.0f;


    };

}


#endif