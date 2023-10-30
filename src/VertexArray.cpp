#include "VertexArray.h"

#include "VertBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RandererID));
}

VertexArray::~VertexArray() 
{
    GLCall(glDeleteVertexArrays(1, &m_RandererID));
}

void VertexArray::AddBufer(const VertexBuffer& vb, const VertBufferLayout& layout)
{
    Bind();
	vb.Bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        //启动顶点属性
        GLCall(glEnableVertexAttribArray(i));
        //设置顶点属性
        GLCall(glVertexAttribPointer(i, element.count, element.type, 
            element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RandererID));
}

void VertexArray::UnBind() const
{
    GLCall(glBindVertexArray(0));
}