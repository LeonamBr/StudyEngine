#include "../../Headers.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

namespace Study {

    VertexArray* VertexArray::Create()
    {

        switch(Renderer::GetAPI()){

            case RendererAPI::API::None: STUDY_CORE_ASSERT(false, "RendererAPI is not suported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();

        }


        STUDY_CORE_ASSERT(false, "Unknow RendererAPI");
        return nullptr;
    }

}