#pragma once



#include "Brain/Events/event.h"
#include "Brain/Core/input.h"



namespace Brain
{
    class Mouse_Move_Event : public Event
    {
        const float x_, y_;
    public:
        Mouse_Move_Event( const float& X, const float& Y )
            :
            x_( X ), y_( Y )
        {}

        const float& x{ x_ };
        const float& y{ y_ };

        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Mouse_Move_Event: ( " << x_ << ", " << y_ << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE( MSE_MOVED );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::MOUSE ) | static_cast<int>( Event_Category::INPUT ) );
    };



    class Mouse_Scroll_Event : public Event
    {
        const float x_offset_, y_offset_;
    public:
        Mouse_Scroll_Event( const float& x_off, const float& y_off )
            :
            x_offset_( x_off ), y_offset_( y_off )
        {}

        const float& x_offset{ x_offset_ };
        const float& y_offset{ y_offset_ };

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "Mouse_Scroll_Event: ( " << x_offset_ << ", " << y_offset_ << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE( MSE_SCROLL );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::MOUSE ) | static_cast<int>( Event_Category::INPUT ) );
    };



    class Mouse_Button_Event : public Event
    {
    public:
        const Mousecode& button{ button_ };

        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::MOUSE ) | static_cast<int>( Event_Category::INPUT ) );
    protected:
        Mouse_Button_Event( Mousecode btn )
            :
            button_( btn )
        {}

        const Mousecode button_;
    };



    class Mouse_Button_Press_Event : public Mouse_Button_Event
    {
    public:
        Mouse_Button_Press_Event( Mousecode btn )
            :
            Mouse_Button_Event( btn )
        {}

        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Mouse_Button_Press_Event: " << button_;
            return ss.str();
        }

        EVENT_CLASS_TYPE( MSE_BUTTON_PRESSED );
    };



    class Mouse_Button_Release_Event : public Mouse_Button_Event
    {
    public:
        Mouse_Button_Release_Event( Mousecode btn )
            :
            Mouse_Button_Event( btn )
        {}

        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Mouse_Button_Release_Event: " << button_;
            return ss.str();
        }

        EVENT_CLASS_TYPE( MSE_BUTTON_RELEASED );
    };
}
