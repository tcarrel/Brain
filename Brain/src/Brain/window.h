#pragma once



#include "br.pch.h"



#include "Brain/nucleus.h"
#include "Brain/Events/event.h"



namespace Brain
{
    struct Window_Properties
    {
        std::string title;
        unsigned width;
        unsigned height;

        Window_Properties( const std::string& T = "Brain Engine", unsigned W = 1280, unsigned H = 720 )
            :
            title( T ),
            width( W ),
            height( H )
        {}
    };


    class BRAIN_API Window
    {
    public:
        using Event_Callback_Function = std::function<void( Event& )>;

        virtual ~Window( void ) = default;

        virtual void on_update( void ) = 0;

        virtual unsigned width( void ) const = 0;
        virtual unsigned height( void ) const = 0;

        // Attributes
        virtual void set_event_callback( const Event_Callback_Function& callback ) = 0;
        virtual void set_vsync( bool enabled ) = 0;
        virtual bool is_vsync_enabled( void ) const = 0;

        static Window* create( const Window_Properties& props = Window_Properties() );
    };
}