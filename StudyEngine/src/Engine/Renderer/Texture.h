#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "../Core/Core.h"

namespace Study {

    class STUDY_API Texture {

        public:

            virtual ~Texture() = default;

            virtual uint32_t GetWidth() const = 0;
            virtual uint32_t GetHeight() const = 0;
            virtual uint32_t GetRendererID() const = 0;

            virtual void SetData(void* data, uint32_t size) = 0;

            virtual void Bind(uint32_t slot = 0) const = 0;

            virtual bool operator==(const Texture& other) const = 0;

    };

    class STUDY_API Texture2D : public Texture {

        public:

            static Shared<Texture2D> Create(uint32_t width, uint32_t height);
            static Shared<Texture2D> Create(const std::string& path);


    };

}

#endif