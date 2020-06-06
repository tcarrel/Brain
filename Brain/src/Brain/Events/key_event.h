#pragma once



#include "Brain/Events/event.h"
#include "Brain/Core/input.h"



namespace Brain
{
    class Keyboard_Event : public Event
    {
    public:
        const Keycode& keycode{ keycode_ };

        EVENT_CLASS_CATEGORY( static_cast<int>( Event_Category::KEYBOARD ) | static_cast<int>( Event_Category::INPUT ) );

    protected:
        Keyboard_Event( Keycode keycode )
            :
            keycode_( keycode )
        {}

        const Keycode keycode_;
    };



    class Key_Press_Event : public Keyboard_Event
    {
    public:
        Key_Press_Event( Keycode code, int repeat_count )
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



    class Key_Release_Event : public Keyboard_Event
    {
    public:
        Key_Release_Event( Keycode keycode )
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



    class Typing_Event : public Keyboard_Event
    {
    public:
        Typing_Event( Keycode kc )
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