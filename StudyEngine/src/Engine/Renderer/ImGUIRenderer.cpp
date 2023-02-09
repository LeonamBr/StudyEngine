#include "../../Headers.h"

#include "ImGUIRenderer.h"

#include <imGUI/imgui.h>

namespace Study {
    
    ImGUIRenderer* ImGUIRenderer::s_Instance = nullptr;

    void ImGUIRenderer::Init(){

        if(s_Instance == nullptr)
            s_Instance = new ImGUIRenderer();

    }

    ImGUIRenderer* ImGUIRenderer::Get(){
        return s_Instance;
    }


    void Study::ImGUIRenderer::Begin(const char* name)
    {

        ImGui::Begin(name);

    }

    void ImGUIRenderer::ColorEdit3(const std::string& name, float* value)
    {
        ImGui::ColorEdit3(name.c_str(), value);
    }
    void ImGUIRenderer::End()
    {
        ImGui::End();
    }
}