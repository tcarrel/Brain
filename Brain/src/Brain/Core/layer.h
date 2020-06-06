#pragma once



//#include "br.pch.h"



#include "Brain/Core/nucleus.h"
#include "Brain/Core/time_step.h"
#include "Brain/Events/event.h"



namespace Brain
{
    class Layer
    {
    public:
        Layer( const std::string& name = "Layer" );
        virtual ~Layer( void );

        virtual void on_attach( void ) {}
        virtual void on_detach( void ) {}
        virtual void on_update( Time_Step ts ) {}
        virtual void on_imgui_render( void ) {}
        virtual void on_event( Event& e ) {}

        const std::string& debug_name{ debug_name_ };

    protected:
        std::string debug_name_;
    };
}