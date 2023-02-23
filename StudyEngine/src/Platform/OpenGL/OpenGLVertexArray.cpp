#include "../../Headers.h"
#include "OpenGLVertexArray.h"

#include <GLAD/glad/glad.h>

namespace Study {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type){

        switch(type){

            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Vec2:  return GL_FLOAT;
            case ShaderDataType::Vec3:  return GL_FLOAT;
            case ShaderDataType::Vec4:  return GL_FLOAT;
            case ShaderDataType::Mat3:  return GL_FLOAT;
            case ShaderDataType::Mat4:  return GL_FLOAT;
            case ShaderDataType::Int:   return GL_INT;
            case ShaderDataType::Int2:  return GL_INT;
            case ShaderDataType::Int3:  return GL_INT;
            case ShaderDataType::Int4:  return GL_INT;
            case ShaderDataType::Bool:  return GL_BOOL;


        }

        STUDY_CORE_ASSERT(false, "Unknown ShaderDataType.");
        return 0;


    }

    OpenGLVertexArray::OpenGLVertexArray() {

        STUDY_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &m_RendererID);


    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        STUDY_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_RendererID);

    }

    void OpenGLVertexArray::Bind() const {

        STUDY_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);

    }

    void OpenGLVertexArray::Unbind() const {

        STUDY_PROFILE_FUNCTION();
        
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Shared<VertexBuffer> &vertexBuffer) {

        STUDY_PROFILE_FUNCTION();

        STUDY_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has not a layout");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout){

            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void*)element.Offset);
            m_VertexBufferIndex++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
        m_VertexBufferIndex += layout.GetElements().size();

    }

    void OpenGLVertexArray::AddIndexBuffer(const Shared<IndexBuffer> &indexBuffer) {

        STUDY_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;

    }
}