#pragma once



#include "nucleus.h"



namespace Brain
{
    struct BRAIN_API Application
    {
        Application();
        virtual ~Application();

        int run( void )
        {
            while( true )
                ;
        }
    };


    /// <summary>
    /// To be created by user in CLIENT application.
    /// </summary>
    Application* create_application( void );
}
