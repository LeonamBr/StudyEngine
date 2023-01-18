#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace Study{

    class STUDY_API Application{

        public:
            Application();
            virtual ~Application();

            void run();

    };

    Application* CreateApplication();

}


#endif