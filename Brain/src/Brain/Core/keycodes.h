#pragma once
#include<sstream>
#include<ostream>



namespace Brain
{
    enum class Keycode : uint16_t
    {
        // From glfw3.h

        space = 32,
        apostrophe = 39,  /* ' */
        comma = 44,  /* , */
        hyphen = 45,  /* - */
        period = 46,  /* . */
        slash = 47,  /* / */
        n0 = 48,
        n1 = 49,
        n2 = 50,
        n3 = 51,
        n4 = 52,
        n5 = 53,
        n6 = 54,
        n7 = 55,
        n8 = 56,
        n9 = 57,
        semicolon = 59,  /* ; */
        equals_sign = 61,  /* = */
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        left_bracket = 91,  /* [ */
        backslash = 92,  /* \ */
        right_bracket = 93,  /* ] */
        grave_accent = 96,  /* ` */
        world_1 = 161, /* non-US #1 */
        world_2 = 162, /* non-US #2 */

        /* Function keys */

        escape = 256,
        enter = 257,
        tab = 258,
        backspace = 259,
        insert = 260,
        del = 261,
        right = 262,
        left = 263,
        down = 264,
        up = 265,
        page_up = 266,
        page_down = 267,
        home = 268,
        end = 269,
        caps_lock = 280,
        scroll_lock = 281,
        num_lock = 282,
        print_screen = 283,
        pause = 284,
        f1 = 290,
        f2 = 291,
        f3 = 292,
        f4 = 293,
        f5 = 294,
        f6 = 295,
        f7 = 296,
        f8 = 297,
        f9 = 298,
        f10 = 299,
        f11 = 300,
        f12 = 301,
        f13 = 302,
        f14 = 303,
        f15 = 304,
        f16 = 305,
        f17 = 306,
        f18 = 307,
        f19 = 308,
        f20 = 309,
        f21 = 310,
        f22 = 311,
        f23 = 312,
        f24 = 313,
        f25 = 314,
        kp0 = 320,
        kp1 = 321,
        kp2 = 322,
        kp3 = 323,
        kp4 = 324,
        kp5 = 325,
        kp6 = 326,
        kp7 = 327,
        kp8 = 328,
        kp9 = 329,
        kpdecimal = 330,
        kpdivide = 331,
        kpmultiply = 332,
        kpsubtract = 333,
        kpadd = 334,
        kpenter = 335,
        kpequal = 336,
        left_shift = 340,
        left_control = 341,
        left_alt = 342,
        left_super = 343,
        left_windows_key = left_super,
        right_shift = 344,
        right_control = 345,
        right_alt = 346,
        right_super = 347,
        right_windows_key = right_super,
        menu = 348,


        forwardslash = slash
    };



    constexpr Keycode to_glfw_keycode( int code )
    {
        switch( code )
        {
        case (int) Keycode::menu:
            return Keycode::menu;
        default:
            return static_cast<Keycode>( code );
        }
    }



    inline std::ostream& operator<<( std::ostream& os, Keycode kc )
    {
        return os << static_cast<uint32_t>( kc );
    }
}