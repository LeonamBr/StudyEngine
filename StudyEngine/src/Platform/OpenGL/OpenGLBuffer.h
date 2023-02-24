#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "../../Engine/Renderer/Buffer.h"

namespace Study {

    class OpenGLVertexBuffer: public VertexBuffer {
        public:
            OpenGLVertexBuffer(uint32_t size);
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            ~OpenGLVertexBuffer();

            virtual void Bind() const;
            virtual void Unbind() const;

            virtual void SetData(const void* data, uint32_t size) override;

            virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
            virtual const BufferLayout& GetLayout () const override { return m_Layout; };

        private:
            uint32_t m_RendererID; 
            BufferLayout m_Layout;


    };

    class OpenGLIndexBuffer: public IndexBuffer {
        public:
            OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
            ~OpenGLIndexBuffer();

            virtual void Bind() const;
            virtual void Unbind() const;

            virtual uint32_t GetCount() const { return m_Count; }

        private:
            uint32_t m_RendererID; 
            uint32_t m_Count;


    };



}

#endif