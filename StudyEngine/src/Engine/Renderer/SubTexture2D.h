#ifndef SUBTEXTURE2D_H
#define SUBTEXTURE2D_H

#include <glm/glm.hpp>

#include "Texture.h"

namespace Study {

    class STUDY_API SubTexture2D
    {
        public:

            SubTexture2D(const Shared<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

            const Shared<Texture2D> GetTexture() const { return m_Texture; }
            const glm::vec2* GetTexCoords() const { return m_TexCoords; }

            static Shared<SubTexture2D> CreateFromCoords(const Shared<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize,const glm::vec2& spriteSize = {1.0f, 1.0f});

        private:

            Shared<Texture2D> m_Texture;

            glm::vec2 m_TexCoords[4];


    };

}

#endif