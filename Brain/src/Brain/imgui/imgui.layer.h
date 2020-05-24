#pragma once



#include "Brain/layer.h"



#include "Brain/Events/app_event.h"
#include "Brain/Events/key_event.h"
#include "Brain/Events/mouse_event.h"



namespace Brain
{
    class BRAIN_API imgui_Layer : public Layer
    {
    public:
        imgui_Layer( const std::string& name = "Default imgui Layer" );
        ~imgui_Layer( void );

        void on_attach( void ) override;
        void on_detach( void )override;
        void on_update( void ) override;
        void on_event( Event& e ) override;

    private:

        bool on_mouse_button_pressed( Mouse_Button_Press_Event& e );
        bool on_mouse_button_released( Mouse_Button_Release_Event& e );
        bool on_mouse_move( Mouse_Move_Event& e );
        bool on_mouse_scroll( Mouse_Scroll_Event& e );
        bool on_key_pressed( Key_Press_Event& e );
        bool on_key_released( Key_Release_Event& e );
        bool on_typing( Typing_Event& e );
        bool on_window_resize( Window_Resize_Event& e );



        float time_{ 0.0 };
    };
}