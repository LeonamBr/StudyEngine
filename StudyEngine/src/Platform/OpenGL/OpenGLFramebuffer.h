#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H

#include "../../Engine/Renderer/Framebuffer.h"
#include "../../Engine/Core/Core.h"

namespace Study {

    class OpenGLFramebuffer : public Framebuffer
    {
        public:

            OpenGLFramebuffer(const FramebufferSpec& spec);
            virtual ~OpenGLFramebuffer();

            void Invalidate();

            virtual void Bind() override;
            virtual void Unbind() override;

            virtual void Resize(uint32_t width, uint32_t height) override;
            virtual int ReadPixel(uint32_t attachmenteIndex, int x, int y) override;

            virtual const FramebufferSpec& GetSpecification() const override { return m_Spec; }
            virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { STUDY_CORE_ASSERT( index < m_ColorAttachments.size(), " "); return m_ColorAttachments[index]; } 

        private:
            uint32_t m_RendererID = 0;
            FramebufferSpec m_Spec;

            std::vector<FramebufferTextureEspecification> m_ColorAttachmentSpecs;
            FramebufferTextureEspecification m_DepthAttachmentSpec = FrameBufferTextureFormat::None;

            std::vector<uint32_t> m_ColorAttachments;
            uint32_t m_DepthAttachment = 0; 

    };

}

#endif