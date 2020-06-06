#pragma once



#include "Brain/Core/nucleus.h"

#include<spdlog/spdlog.h>
#include<spdlog/fmt/ostr.h>



namespace Brain
{
    class Log
    {
    public:
        static void init( void );

        static Ref<spdlog::logger>& get_core_logger( void );
        static Ref<spdlog::logger>& get_client_logger( void );


    private:
        static Ref<spdlog::logger> core_logger_;
        static Ref<spdlog::logger> client_logger_;
    };
}



// Core log macros
#define BR_CORE_ERROR(...)     ::Brain::Log::get_core_logger()->error(      __VA_ARGS__ )
#define BR_CORE_WARN(...)      ::Brain::Log::get_core_logger()->warn(       __VA_ARGS__ )
#define BR_CORE_INFO(...)      ::Brain::Log::get_core_logger()->info(       __VA_ARGS__ )
#define BR_CORE_TRACE(...)     ::Brain::Log::get_core_logger()->trace(      __VA_ARGS__ )
#define BR_CORE_FATAL(...)     ::Brain::Log::get_core_logger()->critical(   __VA_ARGS__ )



// Client log macros
#define BR_ERROR(...)          ::Brain::Log::get_client_logger()->error(    __VA_ARGS__ )
#define BR_WARN(...)           ::Brain::Log::get_client_logger()->warn(     __VA_ARGS__ )
#define BR_INFO(...)           ::Brain::Log::get_client_logger()->info(     __VA_ARGS__ )
#define BR_TRACE(...)          ::Brain::Log::get_client_logger()->trace(    __VA_ARGS__ )
#define BR_FATAL(...)          ::Brain::Log::get_client_logger()->critical( __VA_ARGS__ )
