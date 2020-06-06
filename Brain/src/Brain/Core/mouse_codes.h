#pragma once
#include<ostream>



namespace Brain
{
    enum class Mousecode : uint16_t
    {
        // From glfw3.h

        button_0 = 0,
        button_1 = 1,
        button_2 = 2,
        button_3 = 3,
        button_4 = 4,
        button_5 = 5,
        button_6 = 6,
        button_7 = 7,

        button_last = button_7,
        button_left = button_0,
        button_right = button_1,
        button_middle = button_2
    };




    constexpr Mousecode to_glfw_mse_code( int code )
    {
        switch( code )
        {
        case (int)Mousecode::button_6:
            return Mousecode::button_6;
        default:
            return static_cast<Mousecode>( code );
        }
    }



    inline std::ostream& operator<<( std::ostream& os, Mousecode mc )
    {
        return os << static_cast<uint32_t>( mc );
    }
}
