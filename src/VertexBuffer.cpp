#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RandererID));
    //绑定：意味着我要使用这个缓冲区，缓冲区目标类型GL_ARRAY_BUFFER
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RandererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size, int x)
{
    GLCall(glCreateBuffers(1, &m_RandererID));
    //绑定：意味着我要使用这个缓冲区，缓冲区目标类型GL_ARRAY_BUFFER
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RandererID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER,0, size, data));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RandererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RandererID));
}

void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
