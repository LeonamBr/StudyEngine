#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Event.h"

#include <sstream>

namespace Study{

    class STUDY_API MouseMovedEvent: public Event 
    {

        public:
            MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y){

            }

            inline float GetX() const { return m_MouseX; }
            inline float GetY() const { return m_MouseY; }

            std::string ToString() const override {

            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();

            }

            EVENT_CLASS_TYPE(Moved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        private:
            float m_MouseX, m_MouseY;

    };

    class STUDY_API MouseScrolledEvent : public Event 
    {
        
        public:

            MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset){

            }

            inline float GetXOffset() const { return m_XOffset;  }
            inline float GetYOffset() const { return m_YOffset;  }

            std::string ToString() const override{

                std::stringstream ss;
                ss << "MouseScrolledEvent: " << GetXOffser() << ", " << GetYOffset();
                return ss.str();

            }

            EVENT_CLASS_TYPE(Scrolled)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        private:
            float m_XOffset, m_YOffset;

    };

    class STUDY_API MouseButtonEvent : Event 
    {

        public:

            inline int GetMouseButton() const { return m_Button }

            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        protected:

            MouseButtonEvent(int button) : m_Button {

            }

            int m_Button;

    };

    class STUDY_API MouseButtonPressedEvent : public MouseButtonEvent 
    {

        public:

            MouseButtonPressedEvent(int button) : MouseButtonEvent(button){

            }

            std::string ToString() const override {
                
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_Button;
                return ss.str();

            }

            EVENT_CLASS_TYPE(MBPressed)

    };

    class STUDY_API MouseButtonReleasedEvent : public MouseButtonEvent {

        public:

        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button){

        }

        std::string ToString() const override {

            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();

        }

        EVENT_CLASS_TYPE(MBReleased)

    };

}


#endif