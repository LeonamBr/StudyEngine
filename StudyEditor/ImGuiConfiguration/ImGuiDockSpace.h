#ifndef IMGUIDOCKSPACE_H
#define IMGUIDOCKSPACE_H

#include "ImGuiMenu.h"

namespace Study {

    class ImGuiDockSpace{

        public:

            ImGuiDockSpace();
            ~ImGuiDockSpace() = default;

            void OnAttach();
            void Render();

            static bool s_DockSpace;

    };

}

#endif