#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <memory>

namespace sf
{
    class Log
    {        
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger>& GetCoreLogger();
        static std::shared_ptr<spdlog::logger>& GetClientLogger();
    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
    };
}

#define SF_CORE_TRACE(...) sf::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SF_CORE_INFO(...) sf::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SF_CORE_WARN(...) sf::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SF_CORE_ERROR(...) sf::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SF_CORE_FATAL(...) sf::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#ifdef SF_ENABLE_ASSERTS
    #define SF_ASSERT(x, ...) { if(!(x)) { SF_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define SF_CORE_ASSERT(x, ...) { if(!(x)) { SF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define SF_ASSERT(x, ...)
    #define SF_CORE_ASSERT(x, ...)
#endif