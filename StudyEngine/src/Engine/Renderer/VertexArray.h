#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <memory>
#include "Buffer.h"

namespace Study {

    class STUDY_API VertexArray {

        public:

            virtual ~VertexArray() { }

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) = 0;
            virtual void AddIndexBuffer(const Shared<IndexBuffer>& indexBuffer) = 0;

            virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;
            virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;

            static Shared<VertexArray> Create();

    };

}

#endif