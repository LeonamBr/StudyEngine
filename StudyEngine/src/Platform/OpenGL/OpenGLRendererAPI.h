#ifndef OPENGLRENDERERAPI_H
#define OPENGLRENDERERAPI_H

#include "../../Engine/Renderer/RendererAPI.h"

namespace Study {

    class  OpenGLRendererAPI : public RendererAPI{

        public:
            
            virtual void Init() override;

            virtual void SetClearColor(const glm::vec4& color) override;
            virtual void Clear() override;

            virtual void DrawIndex(const Shared<VertexArray>& vertexArray) override;

    };

}

#endif