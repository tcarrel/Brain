#pragma once



#include "Brain/Core/layer.h"



#include "Brain/Events/app_event.h"
#include "Brain/Events/key_event.h"
#include "Brain/Events/mouse_event.h"



namespace Brain
{
    class imgui_Layer : public Layer
    {
    public:
        imgui_Layer( const std::string& name = "Default imgui Layer" );
        ~imgui_Layer( void );

        void on_attach( void ) override;
        void on_detach( void ) override;

        void begin( void );
        void end( void );
    private:
        float time_{ 0.0 };
    };
}