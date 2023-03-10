#ifndef RENDERER_H
#define RENDERER_H

#include "RendererCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Study {


    class STUDY_API Renderer {

        public:

            static void Init();
            static void Shutdown();
            static void OnWindowResize(uint32_t width, uint32_t height);

            static void BeginScene(OrthographicCamera& camera);
            static void EndScene();

            static void Submit(const Shared<Shader>& shader, const Shared<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); } 
        
        private:
            struct SceneData {

                glm::mat4 ViewProjectionMatrix;

            };

            static Unique<SceneData> s_SceneData;

    };



}

#endif