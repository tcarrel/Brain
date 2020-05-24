#pragma once



#include "Brain/window.h"



struct GLFWwindow;



namespace Brain
{
    class Windows_Window : public Window
    {
    public:
        Windows_Window( const Window_Properties& props );
        virtual ~Windows_Window();

        void on_update() override;

        unsigned width() const override;
        unsigned height() const override;

        // attribs
        void set_event_callback( const Event_Callback_Function& callback ) override;
        void set_vsync( bool enabled ) override;
        bool is_vsync_enabled( void ) const override;

    private:

        virtual void init( const Window_Properties& props );
        virtual void shutdown( void );

        GLFWwindow* window_;

        struct Window_Data
        {
            std::string title;
            unsigned width, height;
            bool vsync;

            Event_Callback_Function event_callback;
        };

        Window_Data data_;
    };
}
