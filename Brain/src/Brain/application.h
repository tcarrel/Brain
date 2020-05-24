#pragma once



#include "nucleus.h"



#include "window.h"
#include "Brain/layer_stack.h"
#include "Brain/Events/event.h"
#include "Brain/Events/app_event.h"



namespace Brain
{
    class BRAIN_API Application
    {
        static Application* instance_;

        std::unique_ptr<Window> window_;
        bool running_;

        Layer_Stack layer_stack_;

        bool on_window_close( Window_Close_Event& e );
    public:
        Application();
        virtual ~Application();

        int run( void );

        void on_event( Event& e );

        void push_layer( Layer* layer );
        void push_overlay( Layer* overlay );

        Window& window( void );

        static Application& get( void );
    };


    /// <summary>
    /// To be created by user in CLIENT application.
    /// </summary>
    Application* create_application( void );
}
