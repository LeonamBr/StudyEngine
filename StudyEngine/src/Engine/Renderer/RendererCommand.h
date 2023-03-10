#ifndef RENDERERCOMMAND_H
#define RENDERERCOMMAND_H

#include "RendererAPI.h"

namespace Study{

    class STUDY_API RendererCommand{

        public:

            inline static void Init(){
                s_RendererAPI->Init();
            }

            inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height){
                s_RendererAPI->SetViewport(x, y, width, height);
            }

            inline static void SetClearColor(const glm::vec4& color){
                s_RendererAPI->SetClearColor(color);
            }

            inline static void Clear(){

                s_RendererAPI->Clear();

            }

            inline static void DrawIndex(const Shared<VertexArray>& vertexArray, uint32_t count = 0){
                s_RendererAPI->DrawIndex(vertexArray, count);
            }

        private:

            static Unique<RendererAPI> s_RendererAPI;


    };

}

#endif