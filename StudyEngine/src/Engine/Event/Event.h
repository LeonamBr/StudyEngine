#ifndef EVENT_H
#define EVENT_H

#include "../../Headers.h"

#include "../Core.h"

#include <string>
#include <functional>

namespace Study{

    enum class EventType{

        None = 0,
        WinClose, WinResize, WinFocus, WinLFocus, WinMoved,
        ApiTick, ApiUpdate, ApiRender,
        kPressed, kReleased,
        MBPressed, MBReleased, Moved, Scrolled

    };

    enum EventCategory{

        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKB             = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMB             = BIT(4)
    };

#define EVENT_CLASS_TYPE(type)      static EventType GetStaticType() { return EventType::type; }\
                                    virtual EventType GetEventType() const override { return GetStaticType(); }\
                                    virtual const char* GetName() const override { return #type; }
    
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class STUDY_API Event{


        public:

            bool m_Handled = false;

            virtual EventType GetEventType() const = 0;
            virtual const char* GetName() const = 0;
            virtual int GetCategoryFlags() const = 0;
            virtual std::string ToString() const { return GetName(); } 

            inline bool IsInCategory(EventCategory category){

                return GetCategoryFlags()& category;

            }

    };

    class EventDispatcher{

        template<typename T>
        using EventFn = std::function<bool(T&)>;

        public:

            EventDispatcher(Event& event) : m_Event(event){

            }

            template<typename T>
            bool Dispatch(EventFn<T> func)
            {

                if(m_Event.GetEventType() == T::GetStaticType())
                {

                    m_Event.m_Handled = func(*(T*)&m_Event);
                    return true;
                }

                return false;

            }

        private:
            Event& m_Event;

    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}

#endif