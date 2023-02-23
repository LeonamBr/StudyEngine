#include "../../Headers.h"

#include "OpenGLBuffer.h"
#include <GLAD/glad/glad.h>

namespace Study {

            OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
            {

                STUDY_PROFILE_FUNCTION();

                glCreateBuffers(1, &m_RendererID);
                glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
                glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

            }

            OpenGLVertexBuffer::~OpenGLVertexBuffer()
            {

                STUDY_PROFILE_FUNCTION();

                glDeleteBuffers(1, &m_RendererID);

            }

            void OpenGLVertexBuffer::Bind() const
            {

                STUDY_PROFILE_FUNCTION();

                glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

            }

            void OpenGLVertexBuffer::Unbind() const
            {

                STUDY_PROFILE_FUNCTION();

                glBindBuffer(GL_ARRAY_BUFFER, 0);

            }

            //###################################

            OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
            {

                STUDY_PROFILE_FUNCTION();

                glCreateBuffers(1, &m_RendererID);
                glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
                glBufferData(GL_ARRAY_BUFFER, count *sizeof(uint32_t), indices, GL_STATIC_DRAW);

            }

            OpenGLIndexBuffer::~OpenGLIndexBuffer()
            {

                STUDY_PROFILE_FUNCTION();

                glDeleteBuffers(1, &m_RendererID);

            }

            void OpenGLIndexBuffer::Bind() const
            {

                STUDY_PROFILE_FUNCTION();

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

            }

            void OpenGLIndexBuffer::Unbind() const
            {

                STUDY_PROFILE_FUNCTION();

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            }

}