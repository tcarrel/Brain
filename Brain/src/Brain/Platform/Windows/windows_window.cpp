#include "br.pch.h"



#include "windows_window.h"
#include "Brain/Events/app_event.h"
#include "Brain/Events/key_event.h"
#include "Brain/Events/mouse_event.h"



#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Brain
{
    static bool GLFW_is_initialized{ false };
    static unsigned Window_Count{ 0 };

    static void GLFW_error_callback( int err, const char* description )
    {
        BR_CORE_ERROR( "GLFW Error: {0}: {1}", err, description );
    }


    Window* Window::create( const Window_Properties& props )
    {
        return new Windows_Window( props );
    }



    Windows_Window::Windows_Window( const Window_Properties& props )
    {
        init( props );
    }



    Windows_Window::~Windows_Window()
    {
        shutdown();
        --Window_Count;
        if( Window_Count == 0 )
        {
            glfwTerminate();
        }
    }



    void Windows_Window::on_update()
    {
        glfwPollEvents();
        glfwSwapBuffers( window_ );
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
        data_.title = props.title;
        data_.width = props.width;
        data_.height = props.height;

        BR_CORE_INFO( "Creating window {0} ({1}x{2})", props.title, props.width, props.height );

        if( !GLFW_is_initialized )
        {
            auto success = glfwInit();
            BR_CORE_ASSERT( success, "Could not initialize GLFW!" );

            glfwSetErrorCallback( GLFW_error_callback );

            GLFW_is_initialized = true;
        }

        window_ = glfwCreateWindow( static_cast<int>( props.width ), static_cast<int>( props.height ), props.title.c_str(), nullptr, nullptr );

        if( window_ )
        {
            ++Window_Count;
        }

        glfwMakeContextCurrent( window_ );

        auto glad_status = gladLoadGLLoader( reinterpret_cast<GLADloadproc>( glfwGetProcAddress ) );
        BR_CORE_ASSERT( glad_status, "Failed to initialize \"glad!\"" );
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
                                    data.event_callback( Key_Press_Event{ key, 0 } );
                                    return;
                                case GLFW_RELEASE:
                                    //Key_Release_Event kre( key );
                                    data.event_callback( Key_Release_Event{ key } );
                                    return;
                                case GLFW_REPEAT:
                                    //Key_Press_Event kpe2( key, 1 );
                                    data.event_callback( Key_Press_Event{ key, 1 } );
                                    return;
                                }
                            } );

        glfwSetCharCallback( window_, []( GLFWwindow* win, unsigned unicode_character )
                             {
                                 auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };
                                 Typing_Event te( unicode_character );
                                 data.event_callback( te );
                             } );

        glfwSetMouseButtonCallback( window_, []( GLFWwindow* win, int button, int action, int mods )
                                    {
                                        auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                        switch( action )
                                        {
                                        case GLFW_PRESS:
                                            //Mouse_Button_Press_Event mbpe( button );
                                            data.event_callback( Mouse_Button_Press_Event{ button } );
                                            return;
                                        case GLFW_RELEASE:
                                            //Mouse_Button_Release_Event mbre( button );
                                            data.event_callback( Mouse_Button_Release_Event{ button } );
                                            return;
                                        }
                                    } );

        glfwSetScrollCallback( window_, []( GLFWwindow* win, double xo, double yo )
                               {
                                   auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                   Mouse_Scroll_Event mse( xo, yo );
                                   data.event_callback( mse );
                               } );

        glfwSetCursorPosCallback( window_, []( GLFWwindow* win, double x, double y )
                                  {
                                      auto& data{ *reinterpret_cast<Window_Data*>( glfwGetWindowUserPointer( win ) ) };

                                      Mouse_Move_Event mme( x, y );
                                      data.event_callback( mme );
                                  } );
    }



    void Windows_Window::shutdown( void )
    {
        glfwDestroyWindow( window_ );
    }
}