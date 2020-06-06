


#include "br.pch.h"



#define IMGUI_IMPL_OPENGL_LOADER_GLAD


#if defined(_MSC_VER)
#   define strcpy strcpy_s
#   define strcat strcat_s
#   define sscanf sscanf_s
// TODO additional macro definitions for different compilers
//#   else
#endif

#include<examples/imgui_impl_opengl3.cpp>
// #undef probably unnecessary, but included just to be extra certain.
#undef sscanf
#undef strcat
#undef strcpy

#include<examples/imgui_impl_glfw.cpp>
