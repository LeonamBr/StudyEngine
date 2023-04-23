#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include <initializer_list>

namespace Study {

    enum class FrameBufferTextureFormat
    {
        None = 0,

        RGBA8,

        RED_INTEGER,

        DEPTH24STENCIL8,

        Depth = DEPTH24STENCIL8

    };

    struct FramebufferTextureEspecification
    {
        FramebufferTextureEspecification() = default;
        FramebufferTextureEspecification(FrameBufferTextureFormat format)
            : TextureFormat(format) {}

            FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
    };

    struct FramebufferAttachmentSpecification
    {

        FramebufferAttachmentSpecification() = default;
        FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureEspecification> attachments)
            : Attachments(attachments) {}

        std::vector<FramebufferTextureEspecification> Attachments;
    };

    struct FramebufferSpec {

        uint32_t Width, Height;
        uint32_t Samples = 1;
        FramebufferAttachmentSpecification Attachments;
        bool SwapChainTarget = false;

    };

    class STUDY_API Framebuffer 
    {
        public: 

            virtual ~Framebuffer() = default;
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual const FramebufferSpec& GetSpecification() const = 0;
            virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0; 

            virtual void Resize(uint32_t width, uint32_t height) = 0;
            virtual int ReadPixel(uint32_t attachmenteIndex, int x, int y) = 0;


            

            static Shared<Framebuffer> Create(const FramebufferSpec& spec);

    };

}

#endif