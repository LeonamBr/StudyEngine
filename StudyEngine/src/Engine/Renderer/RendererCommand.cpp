#include "../../Headers.h"

#include "RendererCommand.h"

#include "../../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Study{

    Unique<RendererAPI> RendererCommand::s_RendererAPI =  CreateUnique<OpenGLRendererAPI>();

}