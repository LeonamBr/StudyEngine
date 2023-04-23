#ifndef EDITORLAYOUT_H
#define EDITORLAYOUT_H

#include "../ImGuiConfiguration/ImGuiMenu.h"
#include "../ImGuiConfiguration/ImGuiDockSpace.h"

#include "../../StudyEngine/src/Engine/Core/Core.h"

namespace Study {

    class EditorLayout {

        public:
            EditorLayout();
            ~EditorLayout() = default;

            void OnAttach();
            void OnImGuiRender();
        
        private:
            
            Shared<ImGuiDockSpace> m_DockSpace;

    };

}

#endif