#include "br.pch.h"

#include "Brain/Core/log.h"
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/basic_file_sink.h>



namespace Brain
{
    Ref<spdlog::logger> Log::core_logger_;
    Ref<spdlog::logger> Log::client_logger_;



    void Log::init( void )
    {
        std::vector<spdlog::sink_ptr> log_sinks;
        log_sinks.emplace_back( create_ref<spdlog::sinks::stderr_color_sink_mt>() );
        log_sinks.emplace_back( create_ref<spdlog::sinks::basic_file_sink_mt>( "brain.log", true ) );

        log_sinks[ 0 ]->set_pattern( "%^[%T] %n\t:\t%v%$" );
        log_sinks[ 1 ]->set_pattern( "[%T] [%l] %n\t:\t%v" );

        core_logger_ = create_ref<spdlog::logger>( "BRAIN", begin( log_sinks ), end( log_sinks ) );
        spdlog::register_logger( core_logger_ );
        core_logger_->set_level( spdlog::level::trace );
        core_logger_->flush_on( spdlog::level::warn );

        client_logger_ = create_ref<spdlog::logger>( "APP  ", begin( log_sinks ), end( log_sinks ) );
        spdlog::register_logger( client_logger_ );
        client_logger_->set_level( spdlog::level::trace );
        client_logger_->flush_on( spdlog::level::warn );
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
