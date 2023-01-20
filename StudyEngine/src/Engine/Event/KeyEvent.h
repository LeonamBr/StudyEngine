#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "Event.h"

#include <sstream>

namespace Study {

    class STUDY_API KeyEvent : public Event
    {

        public:
            inline int GetKeyCode() const { return m_KeyCode; }

            EVENT_CLASS_CATEGORY(EventCategoryKB | EventCategoryInput)

        protected:
            KeyEvent(int keycode) : m_KeyCode(keycode){

            }
        
            int m_KeyCode;
    };

    class STUDY_API KeyPressedEvent : public KeyEvent
    {

        public:
            
            KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount){

            }

            inline int GetRepeatCount() const { return m_RepeatCount; }

            std::string ToString() const override
            {

                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
                return ss.str();

            }

            EVENT_CLASS_TYPE(kPressed)

        private:
            int m_RepeatCount;

    };

    class STUDY_API KeyReleaseEvent : public KeyEvent 
    {

        public: 
            KeyReleaseEvent(int keycode) : KeyEvent(keycode){

            }

        std::string ToString() const override
        {

            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

            EVENT_CLASS_TYPE(kReleased)

    };

    class STUDY_API KeyTypedEvent : public KeyEvent
    {

        public:
            
            KeyTypedEvent(int keycode) : KeyEvent(keycode){

            }



            std::string ToString() const override
            {

                std::stringstream ss;
                ss << "KeyTypedEvent: " << m_KeyCode;
                return ss.str();

            }

            EVENT_CLASS_TYPE(kTyped)

    };

}


#endif