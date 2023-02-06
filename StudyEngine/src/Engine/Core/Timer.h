#ifndef TIMER_H
#define TIMER_H

namespace Study {

    class STUDY_API Timer{

        public:
            Timer(float time) : m_Time(time){

            }

            operator float() const { return m_Time; }

            float GetSeconds() const { return m_Time; }
            float GetMilliseconds() const { return m_Time*1000.0f; }

        private:

            float m_Time;

    };

}

#endif