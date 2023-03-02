#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

namespace Study {

    struct FramebufferSpec {

        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;

    };

    class STUDY_API Framebuffer 
    {
        public: 

            virtual ~Framebuffer() = default;
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual const FramebufferSpec& GetSpecification() const = 0;
            virtual uint32_t GetColorAttachmentRendererID() const = 0; 

            virtual void Resize(uint32_t width, uint32_t height) = 0;


            

            static Shared<Framebuffer> Create(const FramebufferSpec& spec);

    };

}

#endif