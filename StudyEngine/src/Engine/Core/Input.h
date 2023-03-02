#ifndef INPUT_H
#define INPUT_H

#include "Core.h"

namespace Study {

    class STUDY_API Input{

        public:
            
            static bool IsKeyPressed(int keycode);
            
            static bool IsMouseButtonPressed(int button);
            static std::pair<float, float> GetMousePosition();
            static float GetMouseX();
            static float GetMouseY();


    };


}

#endif