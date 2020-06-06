#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>

#include <thread>



namespace Brain
{
    using fp_microseconds = std::chrono::duration<double, std::micro>;



    struct Profile_Result
    {
        std::string name;
        fp_microseconds start;
        std::chrono::microseconds elapsed;
        std::thread::id thread_id;
    };



    struct Instrumentation_Session
    {
        std::string name;
    };



    class Instrumentor
    {
    private:
        std::mutex mutex_;
        Instrumentation_Session* current_session_;
        std::ofstream output_stream_;
    public:
        Instrumentor()
            : current_session_( nullptr )
        {}

        void begin_session( const std::string& name, const std::string& filepath = "results.json" )
        {
            std::lock_guard lock( mutex_ );
            if( current_session_ )
            {
                if( Log::get_core_logger() )
                {
                    BR_CORE_ERROR( "Instrumentor::begin_session('{0}') called when session '{1}' is already open.",
                                   name,
                                   current_session_->name );
                }
                internal_end_session();
            }
            output_stream_.open( filepath );
            if( output_stream_.is_open() )
            {
                current_session_ = new Instrumentation_Session( { name } );
                write_header();
            }
            else
            {
                if( Log::get_core_logger() )
                {
                    BR_CORE_ERROR( "Instrumentor could not open output file '{0}'.", filepath );
                }
            }
        }

        void end_session()
        {
            std::lock_guard lock( mutex_ );
            internal_end_session();
        }

        void write_profile( const Profile_Result& result )
        {
            std::stringstream json;

            std::string name = result.name;
            std::replace( name.begin(), name.end(), '"', '\'' );

            json << "{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << result.elapsed.count() << ',';
            json << "\"name\":\"" << name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.thread_id << ",";
            json << "\"ts\":" << result.start.count();
            json << "}";

            std::lock_guard lock( mutex_ );
            if( current_session_ )
            {
                output_stream_ << json.str() << std::flush;
            }
        }

        static Instrumentor& get()
        {
            static Instrumentor instance;
            return instance;
        }


    private:
        void write_header()
        {
            output_stream_ << "{\"otherData\": {},\"traceEvents\":[ {}" << std::flush;
        }

        void write_footer()
        {
            output_stream_ << "]}" << std::flush;
        }

        void internal_end_session( void )
        {
            if( current_session_ )
            {
                write_footer();
                output_stream_.close();
                delete current_session_;
                current_session_ = nullptr;
            }
        }
    };

    class Instrumentation_Timer
    {
    public:
        Instrumentation_Timer( const char* name )
            : name_( name )
        {}

        ~Instrumentation_Timer()
        {
            if( !stopped_ )
                Stop();
        }

        void Stop()
        {
            const auto end_point{ std::chrono::steady_clock::now() };
            const auto high_resolution_start{ fp_microseconds{ start_.time_since_epoch() } };
            const auto elapsed{ std::chrono::time_point_cast<std::chrono::microseconds>( end_point ).time_since_epoch() };

            Instrumentor::get().write_profile( { name_, high_resolution_start, elapsed, std::this_thread::get_id() } );

            stopped_ = true;
        }
    private:
        const char* name_;
        std::chrono::time_point<std::chrono::steady_clock> start_{ std::chrono::steady_clock::now() };
        bool stopped_{ false };
    };
}


#define BR_PROFILE 0

#if BR_PROFILE
# if defined(__GNUC__) || defined(__MWERKS__) && (__MWERKS__ >= 0x3000) || defined(__ICC) && (__ICC >= 600 ) || defined(__ghs__)
#  define BR_FUNCSIG __PRETTY_FUNCTION__
# elif defined(__DMC__) && (__DMC__ >= 0x810)
#  define BR_FUNCSIG __PRETTY_FUNCTION__
# elif defined(__FUNCSIG__)
#  define BR_FUNCSIG __FUNCSIG__
# elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#  define BR_FUNCSIG __FUNCSIG__
# elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#  define BR_FUNCSIG __FUNC__
# elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#  define BR_FUNCSIG __func__
# elif defined(__cplusplus) && (__cpluspluc >= 201103)
#  define BR_FUNCSIG __func__
# else
#  define BR_FUNCSIG "BR_FUNCSIG Unknown!"
# endif

# define BR_PROFILE_BEGIN_SESSION( name, filepath ) ::Brain::Instrumentor::get().begin_session( name, filepath )
# define BR_PROFILE_END_SESSION() ::Brain::Instrumentor::get().end_session()
# define BR_PROFILE_SCOPE( name ) ::Brain::Instrumentation_Timer timer_##__LINE__( name );
# define BR_PROFILE_FUNCTION() BR_PROFILE_SCOPE( BR_FUNCSIG )
#else
# define BR_PROFILE_BEGIN_SESSION(...)
# define BR_PROFILE_END_SESSION(...)
# define BR_PROFILE_SCOPE(...)
# define BR_PROFILE_FUNCTION(...)
#endif
