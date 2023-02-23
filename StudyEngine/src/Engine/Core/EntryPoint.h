#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "Core.h"

#ifdef STUDY_WINDOWS
    
    extern Study::Application* Study::CreateApplication();

    int main(int argc, char** argv){

        Study::Log::Init();
        
        STUDY_PROFILE_BEGIN_SESSION("Startup", "Startup-Profile.json");
        auto app = Study::CreateApplication();
        STUDY_PROFILE_END_SESSION();

        STUDY_PROFILE_BEGIN_SESSION("Runtime", "RunTime-Profile.json");
        app->run();
        STUDY_PROFILE_END_SESSION();

        STUDY_PROFILE_BEGIN_SESSION("Shutdown", "Shutdown-Profile.json");
        delete app;
        STUDY_PROFILE_END_SESSION();

    }

#else
    #error Only Windows Suport
#endif


#endif