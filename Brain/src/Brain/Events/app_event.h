#pragma once
#include "Brain/Events/event.h"



namespace Brain
{
    class Window_Resize_Event : public Event
    {
        unsigned width_;
        unsigned height_;

    public:
        Window_Resize_Event( unsigned width, unsigned height )
            :
            width_( width ), height_( height )
        {}

        const unsigned& w{ width_ };
        const unsigned& h{ height_ };

        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Window_Resize_Event: ( " << w << 'x' << h << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE( WIN_RESIZE );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::APPLICATION ) );
    };



    class Window_Close_Event : public Event
    {
    public:
        Window_Close_Event() = default;

        EVENT_CLASS_TYPE( WIN_CLOSE );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::APPLICATION ) );
    };



    class App_Tick_Event : public Event
    {
    public:
        App_Tick_Event() = default;

        EVENT_CLASS_TYPE( APP_TICK );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::APPLICATION ) );
    };



    class App_Update_Event : public Event
    {
    public:
        App_Update_Event() = default;

        EVENT_CLASS_TYPE( APP_UPDATE );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::APPLICATION ) );
    };



    class App_Render_Event : public Event
    {
    public:
        App_Render_Event() = default;

        EVENT_CLASS_TYPE( APP_RENDER );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::APPLICATION ) );
    };
}