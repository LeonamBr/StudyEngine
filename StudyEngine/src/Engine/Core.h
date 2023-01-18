#ifndef CORE_H
#define CORE_H

#ifdef STUDY_WINDOWS
    #ifdef STUDY_DLL_BUILD
        #define STUDY_API __declspec(dllexport)
    #else
        #define STUDY_API __declspec(dllimport)
    #endif
#else
    #error Only Windows Suport
#endif

#endif