#include "br.pch.h"

#include "application.h"

#include "input.h"

//Temp
#include <glad/glad.h>



namespace Brain
{
#define BIND_APP_EVENT_FN(f) std::bind( &Application::f, this, std::placeholders::_1 )



    Application* Application::instance_{ nullptr };



    Application::Application()
    {
        BR_CORE_ASSERT( !instance_, "Application already exists!" );
        instance_ = this;

        window_ = std::unique_ptr<Window>( Window::create() );
        window_->set_event_callback( BIND_APP_EVENT_FN( on_event ) );
    }



    bool Application::on_window_close( [[maybe_unused]] Window_Close_Event& e )
    {
        running_ = false;

        return true;
    }



    Window& Application::window( void )
    {
        return *window_;
    }



    Application::~Application()
    {}



    void Application::run( void )
    {
        Window_Resize_Event e( 1280, 720 );

        glClearColor( 1.0f, 0, 1.0f, 1.0f );

        while( running_ )
        {

            for( auto layer : layer_stack_ )
            {
                layer->on_update();
            }

            //auto [x, y] = Input::mouse_position();
            //BR_CORE_TRACE( "{0}x{1}", x, y );

            window_->on_update();

            glClear(GL_COLOR_BUFFER_BIT);
        }
    }



    Application& Application::get( void )
    {
        BR_CORE_ASSERT( instance_, "Application does not exist." );
        return *instance_;
    }



    void Application::on_event( Event& e )
    {
        Event_Dispatch ED{ e };

        ED.dispatch<Window_Close_Event>( BIND_APP_EVENT_FN( on_window_close ) );

        //for( auto it = layer_stack_.end(); it != layer_stack_.begin(); )
        //{
        //    ( *--it )->on_event( e );
        //    if( e.handled )
        //    {
        //        break;
        //    }
        //}

        for( auto it = layer_stack_.rbegin(); it != layer_stack_.rend(); ++it )
        {
            ( *it )->on_event( e );
            if( e.handled )
            {
                break;
            }
        }
    }



    void Application::push_layer( Layer* layer )
    {
        layer_stack_.push( layer );
        layer->on_attach();
    }



    void Application::push_overlay( Layer* overlay )
    {
        layer_stack_.push_overlay( overlay );
        overlay->on_attach();
    }

#undef BIND_APP_EVENT_FN(func)
}
