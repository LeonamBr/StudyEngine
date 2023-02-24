#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Study {

    class STUDY_API RendererAPI {

        public:
            enum class API{
                None = 0, OpenGL = 1
            };
        
        public:
            virtual void Init() = 0;
            virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
            virtual void SetClearColor(const glm::vec4& color) = 0;
            virtual void Clear() = 0;

            virtual void DrawIndex(const Shared<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

            inline static API GetAPI() {return s_API; }

        private:
            static API s_API;
    };

}

#endif