


#include<brain.h>
#include<Brain/Core/entry_point.h>
#include<glm/gtc/matrix_transform.hpp>



#include<imgui/imgui.h>
#include<glm/gtc/type_ptr.hpp>



#include "2d.h"
#include "example_layer.h"



class Sandbox : public Brain::Application
{
public:
    Sandbox()
    {
        //push_layer( new Example_Layer );
        push_layer( new Sandbox_2D );
    }

    ~Sandbox()
    {

    }
};



Brain::Application* Brain::create_application( void )
{
    return new Sandbox;
}