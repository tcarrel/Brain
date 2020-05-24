


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

    }



    void on_event( Brain::Event& e ) override
    {
        BR_TRACE( "{0}", e.to_string() );
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