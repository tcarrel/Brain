#pragma once



#include "event.h"



namespace Brain
{
    class BRAIN_API Mouse_Move_Event : public Event
    {
        const double x_, y_;
    public:
        Mouse_Move_Event( const double& X, const double& Y )
            :
            x_( X ), y_( Y )
        {}

        const double& x{ x_ };
        const double& y{ y_ };

        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Mouse_Move_Event: ( " << x_ << ", " << y_ << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE( MSE_MOVED );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::MOUSE ) | static_cast<int>( Event_Category::INPUT ) );
    };



    class BRAIN_API Mouse_Scroll_Event : public Event
    {
        const double x_offset_, y_offset_;
    public:
        Mouse_Scroll_Event( const double& x_off, const double& y_off )
            :
            x_offset_( x_off ), y_offset_( y_off )
        {}

        const double& x_offset{ x_offset_ };
        const double& y_offset{ y_offset_ };

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "Mouse_Scroll_Event: ( " << x_offset_ << ", " << y_offset_ << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE( MSE_SCROLL );
        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::MOUSE ) | static_cast<int>( Event_Category::INPUT ) );
    };



    class BRAIN_API Mouse_Button_Event : public Event
    {
    public:
        const int& button{ button_ };

        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::MOUSE ) | static_cast<int>( Event_Category::INPUT ) );
    protected:
        Mouse_Button_Event( int btn )
            :
            button_( btn )
        {}

        const int button_;
    };



    class BRAIN_API Mouse_Button_Press_Event : public Mouse_Button_Event
    {
    public:
        Mouse_Button_Press_Event( int btn )
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



    class BRAIN_API Mouse_Button_Release_Event : public Mouse_Button_Event
    {
    public:
        Mouse_Button_Release_Event( int btn )
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
