#include "../StudyEngine/src/Study.h"

#include "Editor/Editor.h"

namespace Study 
{

    class StudyAPI : public Application{

        public:
            StudyAPI(){

                PushLayer(new Editor());

            }
            ~StudyAPI(){}

    };

    Application* CreateApplication(){

        return new StudyAPI();
    }

}