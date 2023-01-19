#ifndef APPLICATIONEVENT_H
#define APPLICATIONEVENT_H

#include "Event.h"

#include <sstream>

namespace Study{

    class STUDY_API WindowResizeEvent : public Event
    {

        public:

                WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height){

                }
                inline unsigned int GetWidth() const { return m_Width; }
                inline unsigned int GetHeight() const { return m_Height; }

                std::string ToString() const override
                {

                    std::stringstream ss;
                    ss << "WndowResizeEvent: " << m_Width << ", " << m_Height;
                    return ss.str();

                }

                EVENT_CLASS_TYPE(WinResize)
                EVENT_CLASS_CATEGORY(EventCategoryApplication)

        private:
            unsigned int m_Width, m_Height;
    };

    class STUDY_API WindowCloseEvent : public Event
    {

        public: 
        
        WindowCloseEvent(){

        }

        EVENT_CLASS_TYPE(WinClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    };

    class STUDY_API AppTickEvent : public Event
    {
        public:

            AppTickEvent(){

            }

            EVENT_CLASS_TYPE(ApiTick)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class STUDY_API AppUpdateEvent : public Event
    {
        public:

            AppUpdateEvent(){

            }

            EVENT_CLASS_TYPE(ApiUpdate)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class STUDY_API AppRenderEvent : public Event
    {
        public:

            AppRenderEvent(){

            }

            EVENT_CLASS_TYPE(ApiRender)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

}


#endif