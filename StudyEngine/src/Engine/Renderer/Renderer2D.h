#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "OrthographicCamera.h"

#include "Texture.h"

namespace Study {

    class STUDY_API Renderer2D {

        public:

            static void Init();
            static void Shutdown();

            static void BeginScene(const OrthographicCamera& camera);
            static void EndScene();
            static void Flush();

            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});

            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& colorize = glm::vec4{1.0f});

    };

}

#endif