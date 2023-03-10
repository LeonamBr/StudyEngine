#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include "../../Engine/Renderer/VertexArray.h"

namespace Study {

    class OpenGLVertexArray : public VertexArray{

        public:

            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) override;
            virtual void AddIndexBuffer(const Shared<IndexBuffer>& indexBuffer) override;

            virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
            virtual const Shared<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

        private:

            uint32_t m_RendererID;
            uint32_t m_VertexBufferIndex = 0;
            std::vector<Shared<VertexBuffer>> m_VertexBuffers;
            Shared<IndexBuffer> m_IndexBuffer;

    };
}

#endif