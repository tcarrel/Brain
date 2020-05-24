#pragma once



#if defined(BR_PLATFORM_WINDOWS)



extern Brain::Application* Brain::create_application( void );



int main( int argc, char* argv[] )
{
    Brain::Log::init();
    BR_CORE_WARN( "Core Logger Initialized!" );
    BR_INFO( "Client Logger Initialized!" );

    auto sandbox = Brain::create_application();
    auto exit_status = sandbox->run();
    delete sandbox;

    return exit_status;
}
#endif // defined(BR_PLATFORM_WINDOWS)

