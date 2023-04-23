#ifndef SCRIPTABLEENTITY_H
#define SCRIPTABLEENTITY_H

#include "Entity.h"

namespace Study {

    class STUDY_API ScriptableEntity {

        public:

            virtual ~ScriptableEntity() {}

            template<typename T>
            T& GetComponent()
            {
                return m_Entity.GetComponent<T>();
            }
        
        protected:
            virtual void OnCreate() {}
            virtual void OnDestroy() {}
            virtual void OnUpdate(Timer timeStep) {}

        private:
            Entity m_Entity;
            friend class Scene;

    };

}
#endif