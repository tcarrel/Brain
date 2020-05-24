#pragma once



#if defined(BR_PLATFORM_WINDOWS)



extern Brain::Application* Brain::create_application( void );



int main( int argc, char* argv[] )
{
    Brain::Log::init();
    BR_CORE_TRACE( "Core Logger Initialized!" );
    //BR_CORE_TRACE( "Trace Test " );
    //BR_CORE_INFO( "Info Test" );
    //BR_CORE_WARN( "Warning Test" );
    //BR_CORE_ERROR( "Error Test" );
    //BR_CORE_FATAL( "Fatal Test" );

    BR_TRACE( "Client Logger Initialized!" );
    //BR_TRACE( "Trace Test " );
    //BR_INFO( "Info Test" );
    //BR_WARN( "Warning Test" );
    //BR_ERROR( "Error Test" );
    //BR_FATAL( "Fatal Test" );

    auto sandbox = Brain::create_application();
    sandbox->run();
    delete sandbox;

    return argc - 1;
}
#endif // defined(BR_PLATFORM_WINDOWS)

