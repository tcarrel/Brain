#include "br.pch.h"

#include "Brain/Core/application.h"

#include "Brain/Core/input.h"
#include "Brain/Core/log.h"
#include "Brain/Renderer/renderer.h"



#include<GLFW/glfw3.h>



namespace Brain
{
    Application* Application::instance_{ nullptr };



    Application::Application()
    {
        BR_PROFILE_FUNCTION();

        BR_CORE_ASSERT( !instance_, "Application already exists!" );
        instance_ = this;

        window_ = Window::create();
        window_->set_event_callback( BR_BIND_EVENT_FUNCTION( Application::on_event ) );

        Renderer::init();

        imgui_layer_ = new imgui_Layer;
        push_overlay( imgui_layer_ );

    }



    bool Application::on_window_close( [[maybe_unused]] Window_Close_Event& e )
    {
        running_ = false;

        return true;
    }



    bool Application::on_window_resize( Window_Resize_Event& e )
    {
        BR_PROFILE_FUNCTION();

        if( e.w == 0 || e.h == 0 )
        {
            minimized_ = true;
            return false;
        }
        minimized_ = false;
        Renderer::on_window_resize( e.w, e.h );

        return false;
    }



    Window& Application::window( void )
    {
        return *window_;
    }



    Application::~Application()
    {
        BR_PROFILE_FUNCTION();

        Renderer::shutdown();
    }



    void Application::run( void )
    {
        BR_PROFILE_FUNCTION();

        Window_Resize_Event e( 1280, 720 );

        while( running_ )
        { 
            BR_PROFILE_SCOPE( "Main Loop" );

            float time = static_cast<float>( glfwGetTime() );
            Time_Step time_step{ time - last_frame_time_ };
            last_frame_time_ = time;

            if( !minimized_ )
            {
                BR_PROFILE_SCOPE("Update Layers");
                for( auto layer : layer_stack_ )
                {
                    layer->on_update( time_step );
                }
            }

            {
                BR_PROFILE_SCOPE( "Application ImGui Render" );
                imgui_layer_->begin();
                for( auto layer : layer_stack_ )
                {
                    layer->on_imgui_render();
                }
                imgui_layer_->end();
            }

            window_->on_update();

        }
    }



    Application& Application::get( void )
    {
        BR_CORE_ASSERT( instance_, "Application does not exist." );
        return *instance_;
    }



    void Application::on_event( Event& e )
    {
        BR_PROFILE_FUNCTION();

        Event_Dispatch ED{ e };

        ED.dispatch<Window_Close_Event>( BR_BIND_EVENT_FUNCTION( Application::on_window_close ) );
        ED.dispatch<Window_Resize_Event>( BR_BIND_EVENT_FUNCTION( Application::on_window_resize ) );

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
        BR_PROFILE_FUNCTION();

        layer_stack_.push( layer );
        layer->on_attach();
    }



    void Application::push_overlay( Layer* overlay )
    {
        BR_PROFILE_FUNCTION();

        layer_stack_.push_overlay( overlay );
        overlay->on_attach();
    }

#undef BR_BIND_APP_EVENT_FN
}
