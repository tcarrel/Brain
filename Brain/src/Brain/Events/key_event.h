#pragma once



#include "event.h"



namespace Brain
{
    class BRAIN_API Keyboard_Event : public Event
    {
    public:
        const int& keycode{ keycode_ };

        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::KEYBOARD ) | static_cast<int>( Event_Category::INPUT ) );

    protected:
        Keyboard_Event( int keycode )
            :
            keycode_( keycode )
        {}

        const int keycode_;
    };



    class BRAIN_API Key_Press_Event : public Keyboard_Event
    {
    public:
        Key_Press_Event( int code, int repeat_count )
            :
            Keyboard_Event( code ),
            repeat_count_( repeat_count )
        {}

        const int& repeat_count{ repeat_count_ };

        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Key_Press_Event: " << keycode_ << " ( " << repeat_count_ << " repeats )";
            return ss.str();
        }

        EVENT_CLASS_TYPE( KEY_PRESSED );

    private:
        int repeat_count_{ 0 };
    };



    class BRAIN_API Key_Release_Event : public Keyboard_Event
    {
    public:
        Key_Release_Event( int keycode )
            :
            Keyboard_Event( keycode )
        {}

        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Key_Release_Event: " << keycode_;
            return ss.str();
        }

        EVENT_CLASS_TYPE( KEY_RELEASED );
    };



    class BRAIN_API Typing_Event : public Keyboard_Event
    {
    public:
        Typing_Event( int kc )
            :
            Keyboard_Event( kc )
        {}
        

        
        std::string to_string( void ) const override
        {
            std::stringstream ss;
            ss << "Typing_Event" << keycode;
            return ss.str();
        }

        EVENT_CLASS_TYPE( KEY_TYPING );
    };
}