#ifndef RENDERERCOMMAND_H
#define RENDERERCOMMAND_H

#include "RendererAPI.h"

namespace Study{

    class STUDY_API RendererCommand{

        public:

            inline static void Init(){
                s_RendererAPI->Init();
            }

            inline static void SetClearColor(const glm::vec4& color){
                s_RendererAPI->SetClearColor(color);
            }

            inline static void Clear(){

                s_RendererAPI->Clear();

            }

            inline static void DrawIndex(const Shared<VertexArray>& vertexArray){
                s_RendererAPI->DrawIndex(vertexArray);
            }

        private:

            static RendererAPI* s_RendererAPI;


    };

}

#endif