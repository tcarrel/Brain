#include "br.pch.h"



#include "Platform/Windows/windows_window.h"
#include "Brain/Events/app_event.h"
#include "Brain/Events/key_event.h"
#include "Brain/Events/mouse_event.h"
#include "Brain/Renderer/renderer.h"



#include "Brain/Core/input.h"



#include "Platform/OpenGL/opengl_context.h"



namespace Brain
{
    static unsigned Window_Count{ 0 };

    static void GLFW_error_callback( int err, const char* description )
    {
        BR_CORE_ERROR( "GLFW Error: {0}: {1}", err, description );
    }



    Windows_Window::Windows_Window( const Window_Properties& props )
    {
        BR_PROFILE_FUNCTION();
        init( props );
    }



    Windows_Window::~Windows_Window()
    {
        BR_PROFILE_FUNCTION();
        shutdown();
    }



    void Windows_Window::on_update()
    {
        BR_PROFILE_FUNCTION();
        glfwPollEvents();
        context_->swap_buffers();
    }



    unsigned Windows_Window::width() const
    {
        return data_.width;
    }



    unsigned Windows_Window::height() const
    {
        return data_.height;
    }



    void* Windows_Window::get_native_window( void ) const
    {
        return window_;
    }



    void Windows_Window::set_event_callback( const Event_Callback_Function& callback )
    {
        data_.event_callback = callback;
    }



    void Windows_Window::set_vsync( bool enabled )
    {
        BR_PROFILE_FUNCTION();

        if( enabled )
        {
            glfwSwapInterval( 1 );
        }
        else
        {
            glfwSwapInterval( 0 );
        }

        data_.vsync = enabled;
    }



    bool Windows_Window::is_vsync_enabled( void ) const
    {
        return data_.vsync;
    }


    void Windows_Window::init( const Window_Properties& props )
    {
        BR_PROFILE_FUNCTION();
        data_.title = props.title;
        data_.width = props.width;
        data_.height = props.height;

        BR_CORE_INFO( "Creating window {0} ({1}x{2})", props.title, props.width, props.height );

        if( Window_Count == 0 )
        {
            BR_PROFILE_SCOPE( "glfwInit" );

            auto success = glfwInit();
            BR_CORE_ASSERT( success, "Could not initialize GLFW!" );

            glfwSetErrorCallback( GLFW_error_callback );
        }

        {
            BR_PROFILE_SCOPE( "glfwCreateWindow" );
#if defined(BR_DEBUG)
            if( Renderer::get_api() == Renderer_API::API::OpenGL )
            {
                glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE );
            }
#endif
            window_ = glfwCreateWindow( static_cast<int>( props.width ), static_cast<int>( props.height ), props.title.c_str(), nullptr, nullptr );
            if( window_ )
            {
                ++Window_Count;
            }
            else
            {
                BR_CORE_ASSERT( false, "Could not create window" );
            }
        }

        context_ = Render_Context::create( window_ );

        
        context_->init();

        glfwSetWindowUserPointer( window_, &data_ );
        set_vsync( true );

        // Set GLFW callbacks
        glfwSetWindowSizeCallback( window_, []( GLFWwindow* win, int w, int h )
                                   {
                                       auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };
                                       data.width = w;
                                       data.height = h;

                                       Window_Resize_Event wre{ static_cast<unsigned>( w ), static_cast<unsigned>( h ) };
                                       data.event_callback( wre );

                                   } );

        glfwSetWindowCloseCallback( window_, []( GLFWwindow* win )
                                    {
                                        auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                        Window_Close_Event wcs;
                                        data.event_callback( wcs );
                                    } );

        glfwSetKeyCallback( window_, []( GLFWwindow* win, int key, int scancode, int act, int mods )
                            {
                                auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                switch( act )
                                {
                                case GLFW_PRESS:
                                    //Key_Press_Event kpe( key, 0 );
                                    data.event_callback( Key_Press_Event{ static_cast<Keycode>( key ), 0 } );
                                    return;
                                case GLFW_RELEASE:
                                    //Key_Release_Event kre( key );
                                    data.event_callback( Key_Release_Event{ static_cast<Keycode>( key ) } );
                                    return;
                                case GLFW_REPEAT:
                                    //Key_Press_Event kpe2( key, 1 );
                                    data.event_callback( Key_Press_Event{ static_cast<Keycode>( key ), 1 } );
                                    return;
                                }
                            } );

        glfwSetCharCallback( window_, []( GLFWwindow* win, unsigned unicode_character )
                             {
                                 auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };
                                 Typing_Event te( static_cast<Keycode>( unicode_character ) );
                                 data.event_callback( te );
                             } );

        glfwSetMouseButtonCallback( window_, []( GLFWwindow* win, int button, int action, int mods )
                                    {
                                        auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                        switch( action )
                                        {
                                        case GLFW_PRESS:
                                            //Mouse_Button_Press_Event mbpe( button );
                                            data.event_callback( Mouse_Button_Press_Event{ static_cast<Mousecode>( button ) } );
                                            return;
                                        case GLFW_RELEASE:
                                            //Mouse_Button_Release_Event mbre( button );
                                            data.event_callback( Mouse_Button_Release_Event{ static_cast<Mousecode>( button ) } );
                                            return;
                                        }
                                    } );

        glfwSetScrollCallback( window_, []( GLFWwindow* win, double xo, double yo )
                               {
                                   auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                   Mouse_Scroll_Event mse( static_cast<float>( xo ), static_cast<float>( yo ) );
                                   data.event_callback( mse );
                               } );

        glfwSetCursorPosCallback( window_, []( GLFWwindow* win, double x, double y )
                                  {
                                      auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                      Mouse_Move_Event mme( static_cast<float>( x ), static_cast<float>( y ) );
                                      data.event_callback( mme );
                                  } );
    }



    void Windows_Window::shutdown( void )
    {
        BR_PROFILE_FUNCTION();
        glfwDestroyWindow( window_ );
        --Window_Count;
        if( Window_Count == 0 )
        {
            BR_CORE_INFO( "Terminating GLFW" );
            glfwTerminate();
        }
    }
}