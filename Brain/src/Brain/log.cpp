#include "br.pch.h"

#include "log.h"


#include "spdlog/sinks/stdout_color_sinks.h"



namespace Brain
{
    std::shared_ptr<spdlog::logger> Log::core_logger_;
    std::shared_ptr<spdlog::logger> Log::client_logger_;



    void Log::init( void )
    {
        spdlog::set_pattern( "%^[%T] %n: %v%$" );
        core_logger_ = spdlog::stdout_color_mt( "BRAIN" );
        core_logger_->set_level( spdlog::level::trace );
        client_logger_ = spdlog::stderr_color_mt( "APP  " );
        client_logger_->set_level( spdlog::level::trace );
    }



    std::shared_ptr<spdlog::logger>& Log::get_core_logger( void )
    {
        return core_logger_;
    }



    std::shared_ptr<spdlog::logger>& Log::get_client_logger( void )
    {
        return client_logger_;
    }
}