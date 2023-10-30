#pragma once

#include "VertexBuffer.h"
 
class VertBufferLayout;

class VertexArray
{
private:
	unsigned int m_RandererID;

public:
	VertexArray();
	~VertexArray();

	void AddBufer(const VertexBuffer& vb, const VertBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};
