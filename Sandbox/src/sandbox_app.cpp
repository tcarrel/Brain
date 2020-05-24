


#include<brain.h>



class Example_Layer : public Brain::Layer
{
public:
    Example_Layer( void )
        :
        Layer( "Example" )
    {}



    void on_update( void ) override
    {
        if( Brain::Input::is_key_pressed( BR_KEY_TAB ) )
        {
            BR_TRACE( "Tab key is pressed!" );
        }
    }



    void on_event( Brain::Event& e ) override
    {
        if( e.get_event_type() == Brain::Event_Type::KEY_PRESSED )
        {
            auto kpe{ reinterpret_cast<Brain::Key_Press_Event&>( e ) };
            BR_TRACE( "{0}", (char)kpe.keycode );
        }
    }
};


class Sandbox : public Brain::Application
{
public:
    Sandbox()
    {
        push_layer( new Example_Layer );
        push_overlay( new Brain::imgui_Layer );
    }

    ~Sandbox()
    {

    }
};



Brain::Application* Brain::create_application( void )
{
    return new Sandbox;
}