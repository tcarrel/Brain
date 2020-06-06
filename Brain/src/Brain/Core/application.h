#pragma once



#include "Brain/Core/nucleus.h"



#include "Brain/Core/window.h"
#include "Brain/Core/layer_stack.h"
#include "Brain/Events/event.h"
#include "Brain/Events/app_event.h"



#include "Brain/imgui/imgui.layer.h"

#include "Brain/Core/time_step.h"



int main( int argc, char* argv[] );



namespace Brain
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void on_event( Event& e );

        void push_layer( Layer* layer );
        void push_overlay( Layer* overlay );

        Window& window( void );

        static Application& get( void );

    private:

        void run( void );

        static Application* instance_;

        std::unique_ptr<Window> window_;
        imgui_Layer* imgui_layer_{ nullptr };
        bool running_{ true };

        Layer_Stack layer_stack_;

        float last_frame_time_{ 0.0f };

        bool minimized_{ false };



        bool on_window_close( Window_Close_Event& e );
        bool on_window_resize( Window_Resize_Event& e );



        friend int ::main( int argc, char* argv[] );
    };


    /// <summary>
    /// To be created by user in CLIENT application.
    /// </summary>
    Application* create_application( void );
}
