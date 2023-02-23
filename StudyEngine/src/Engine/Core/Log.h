#ifndef LOG_H
#define LOG_H

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Study{

    class STUDY_API Log{

        public:

            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){return s_CoreLogger;}
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){return s_ClientLogger;}

        private:

            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;



    };

}


//core log Macros
#define STUDY_CORE_TRACE(...)   ::Study::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define STUDY_CORE_INFO(...)    ::Study::Log::GetCoreLogger()->info(__VA_ARGS__)
#define STUDY_CORE_WARN(...)    ::Study::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define STUDY_CORE_ERROR(...)   ::Study::Log::GetCoreLogger()->error(__VA_ARGS__)
#define STUDY_CORE_CRITICAL(...)   ::Study::Log::GetCoreLogger()->critical(__VA_ARGS__)

//client log
#define STUDY_TRACE(...)   ::Study::Log::GetClientLogger()->trace(__VA_ARGS__)
#define STUDY_INFO(...)    ::Study::Log::GetClientLogger()->info(__VA_ARGS__)
#define STUDY_WARN(...)    ::Study::Log::GetClientLogger()->warn(__VA_ARGS__)
#define STUDY_ERROR(...)   ::Study::Log::GetClientLogger()->error(__VA_ARGS__)
#define STUDY_CRITICAL(...)   ::Study::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif
