#include "../../Headers.h"

#include "RendererCommand.h"

#include "../../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Study{

    RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;

}