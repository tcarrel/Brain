#pragma once



#include "Brain/Core/nucleus.h"



#if defined(BR_PLATFORM_WINDOWS)



extern Brain::Application* Brain::create_application( void );



int main( int argc, char* argv[] )
{
    Brain::Log::init();

    BR_PROFILE_BEGIN_SESSION( "Start Up", "Brain_Profile-startup.json" );
    auto sandbox = Brain::create_application();
    BR_PROFILE_END_SESSION();

    BR_PROFILE_BEGIN_SESSION( "Runtime", "Brain_Profile-runtime.json" );
    sandbox->run();
    BR_PROFILE_END_SESSION();

    BR_PROFILE_BEGIN_SESSION( "Shutdown", "Brain_Profile-shutdown.json" );
    delete sandbox;
    BR_PROFILE_END_SESSION();

    return argc - 1;
}
#endif // defined(BR_PLATFORM_WINDOWS)

