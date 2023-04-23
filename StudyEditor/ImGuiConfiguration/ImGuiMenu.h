#ifndef IMGUIMENU_H
#define IMGUIMENU_H

#include "../../StudyEngine/src/Study.h"

#include "../../StudyEngine/include/imGUI/imgui.h"
#include "../../StudyEngine/src/Engine/Scene/SceneSerializer.h"
#include "../../StudyEngine/src/Engine/Utils/PlatformUtils.h"
#include "ViewPort.h"

#include "../../StudyEngine/src/Engine/Core/Core.h"

#include "../Panels/SceneHierarchyPanel.h"

namespace Study {

    enum class SerializerState {
        isRunning = 0,
        onCreate,
        onLoad,
        onSaving
    };

    class ImGuiMenu {

        public: 

            ImGuiMenu();
            ~ImGuiMenu() = default;

            void OnAttach();
            void SetScene(Shared<Scene>& scene);
            SerializerState Render(Shared<ViewPort>& viewport, Shared<SceneHierarchyPanel>& sceneHierarchyPanel);
        
        private:
        
            void ImGuiTool();

        private:

            Shared<Scene> m_Scene;  


    };

}

#endif