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

#ifdef STUDY_ENABLE_ASSERTS
	#define STUDY_ASSERT(x, ...) { if(!(x)) { STUDY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define STUDY_CORE_ASSERT(x, ...) { if(!(x)) { STUDY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define STUDY_ASSERT(x, ...)
	#define STUDY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#endif