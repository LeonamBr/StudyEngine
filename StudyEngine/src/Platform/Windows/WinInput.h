#ifndef WININPUT_H
#define WININPUT_H

#include "../../Engine/Core/Input.h"
namespace Study{

    class WinInput : public Input{

        protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override; 
        virtual float GetMouseXImpl() override; 
        virtual float GetMouseYImpl() override;

    };

}


#endif