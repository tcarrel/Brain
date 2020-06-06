#pragma once



#include "Brain/Core/time_step.h"
#include "Brain/Renderer/orthographic_camera.h"



#include "Brain/Events/mouse_event.h"
#include "Brain/Events/app_event.h"



#include "Brain/Core/input.h"
#include "Brain/Core/keycodes.h"
#include "Brain/Core/mouse_codes.h"



namespace Brain
{
    class Orthographic_Camera_Controller
    {
    public:
        Orthographic_Camera_Controller( float aspect_ratio, bool rotation_enable = false );

        void on_update( Time_Step ts );
        void on_event( Event& e );

        Orthographic_Camera& get_camera( void );
        const Orthographic_Camera& get_camera( void ) const;

    private:
        bool on_mouse_scrolled( Mouse_Scroll_Event& e );
        bool on_window_resize( Window_Resize_Event& e );



        float aspect_ratio_{ 16.0f / 9.0f };
        float zoom_level_{ 1.0 };
        Orthographic_Camera camera_;

        const bool ALLOW_ROTATION_{ false };
        glm::vec3 position_{ 0.0f, 0.0f, 0.0f };
        float rotation_{ 0.0 };

        float translation_speed_{ 5.0f };
        float rotation_speed_{ 180.0f };
    };
}