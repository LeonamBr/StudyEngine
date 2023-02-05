#ifndef RENDERER_H
#define RENDERER_H

#include "RendererCommand.h"

namespace Study {


    class STUDY_API Renderer {

        public:

            static void BeginScene();
            static void EndScene();

            static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); } 

    };



}

#endif