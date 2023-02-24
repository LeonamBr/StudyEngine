#include "../../Headers.h"

#include "Buffer.h"
#include "Renderer.h"

#include "../../Platform/OpenGL/OpenGLBuffer.h"

namespace Study {

    Shared<VertexBuffer> VertexBuffer::Create(uint32_t size){

        switch (Renderer::GetAPI()){

            case RendererAPI::API::None: {

                STUDY_CORE_ASSERT(false, "RendererAPI::None is Currently not suported.");
                return nullptr;    
            }
                
            case RendererAPI::API::OpenGL:
                return  CreateShared<OpenGLVertexBuffer>(size);

        }

        STUDY_CORE_ASSERT(false, "Unknow Renderer API!");
        return nullptr;


    }

    Shared<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size){

        switch (Renderer::GetAPI()){

            case RendererAPI::API::None: {

                STUDY_CORE_ASSERT(false, "RendererAPI::None is Currently not suported.");
                return nullptr;    
            }
                
            case RendererAPI::API::OpenGL:
                return  CreateShared<OpenGLVertexBuffer>(vertices, size);

        }

        STUDY_CORE_ASSERT(false, "Unknow Renderer API!");
        return nullptr;


    }

    Shared<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size){

         switch (Renderer::GetAPI()){

            case RendererAPI::API::None: {

                STUDY_CORE_ASSERT(false, "RendererAPI::None is Currently not suported.");
                return nullptr;    
            }
                
            case RendererAPI::API::OpenGL:
                return CreateShared<OpenGLIndexBuffer>(indices, size);

        }

        STUDY_CORE_ASSERT(false, "Unknow Renderer API!");
        return nullptr;

    }


}