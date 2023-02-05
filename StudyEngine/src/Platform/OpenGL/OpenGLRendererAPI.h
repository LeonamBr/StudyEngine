#ifndef OPENGLRENDERERAPI_H
#define OPENGLRENDERERAPI_H

#include "../../Engine/Renderer/RendererAPI.h"

namespace Study {

    class  OpenGLRendererAPI : public RendererAPI{

        public:
            
            virtual void SetClearColor(const glm::vec4& color) override;
            virtual void Clear() override;

            virtual void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) override;

    };

}

#endif