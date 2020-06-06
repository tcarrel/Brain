#include "br.pch.h"



#include "Brain/Renderer/render_command.h"



namespace Brain
{
    Scope<Renderer_API> Render_Command::renderer_api_ = Renderer_API::create();
}