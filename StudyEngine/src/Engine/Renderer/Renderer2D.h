#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "OrthographicCamera.h"
#include "Camera.h"
#include "../Scene/EditorCamera.h"

#include "Texture.h"
#include "SubTexture2D.h"

namespace Study {

    class STUDY_API Renderer2D {

        public:

            static void Init();
            static void Shutdown();

            static void BeginScene(const Camera& camera, const glm::mat4& transform);
            static void BeginScene(const EditorCamera& camera);
            static void BeginScene(const OrthographicCamera& camera);
            static void EndScene();
            static void Flush();

            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<SubTexture2D>& subtexture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<SubTexture2D>& subtexture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});

            static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
            static void DrawQuad(const glm::mat4& transform, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});

            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Shared<SubTexture2D>& subtexture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Shared<SubTexture2D>& subtexture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});

            struct Statistics
            {
                uint32_t DrawCalls = 0;
                uint32_t QuadCount = 0;

                uint32_t GetTotalVertexCount() { return QuadCount * 4; }
                uint32_t GetTotalIndexCount() { return QuadCount * 6; }

            };

            static void ResetStats();
            static Statistics GetStats();

        private:

            static void StartNewBatch();

    };

}

#endif