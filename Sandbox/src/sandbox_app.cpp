


#include<brain.h>



struct Sandbox : public Brain::Application
{
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};



Brain::Application* Brain::create_application( void )
{
    return new Sandbox;
}