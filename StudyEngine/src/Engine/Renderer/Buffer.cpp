#include "../../Headers.h"

#include "Buffer.h"
#include "Renderer.h"

#include "../../Platform/OpenGL/OpenGLBuffer.h"

namespace Study {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){

        switch (Renderer::GetAPI()){

            case RendererAPI::API::None: {

                STUDY_CORE_ASSERT(false, "RendererAPI::None is Currently not suported.");
                return nullptr;    
            }
                
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);

        }

        STUDY_CORE_ASSERT(false, "Unknow Renderer API!");
        return nullptr;


    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){

         switch (Renderer::GetAPI()){

            case RendererAPI::API::None: {

                STUDY_CORE_ASSERT(false, "RendererAPI::None is Currently not suported.");
                return nullptr;    
            }
                
            case RendererAPI::API::OpenGL:
                return new OpenGLIndexBuffer(indices, size);

        }

        STUDY_CORE_ASSERT(false, "Unknow Renderer API!");
        return nullptr;

    }


}