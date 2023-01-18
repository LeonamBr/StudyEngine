#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#ifdef STUDY_WINDOWS
    
    extern Study::Application* Study::CreateApplication();

    int main(int argc, char** argv){

        Study::Log::Init();
        STUDY_CORE_WARN("Testando o core logger");
        STUDY_INFO("Tesando o Client logger");

        auto app = Study::CreateApplication();
        app->run();
        delete app;

    }

#else
    #error Only Windows Suport
#endif


#endif