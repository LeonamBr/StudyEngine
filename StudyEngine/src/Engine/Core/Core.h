#ifndef CORE_H
#define CORE_H

#include <memory>

#ifdef _WIN32
    #ifdef _WIN64
        #define STUDY_WINDOWS
    #else
        #error "x86 Builders is not suported"
    #endif
#endif

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

#define STUDY_BIND_EVENT_FN(x) [this](auto&&... args) -> decltype(auto) { return this->x(std::forward<decltype(args)>(args)...); }

namespace Study {

    template<typename T>
    using Unique = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Unique<T> CreateUnique(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args) ...);
    }

    template<typename T>
    using Shared = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Shared<T> CreateShared(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args) ...);
    }

}

#endif