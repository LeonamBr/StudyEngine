#include "../../Headers.h"

#include "Framebuffer.h"

#include "Renderer.h"

#include "../../Platform/OpenGL/OpenGLFramebuffer.h"

namespace Study {

    
    
Shared<Framebuffer> Framebuffer::Create(const FramebufferSpec & spec)
{
    switch(Renderer::GetAPI()){

            case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateShared<OpenGLFramebuffer>(spec);

        }


        STUDY_CORE_ASSERT(false, "Unknow RendererAPI");
        return nullptr;
}

}