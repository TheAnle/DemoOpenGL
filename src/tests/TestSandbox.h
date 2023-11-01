#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertBufferLayout.h"
#include "Texture.h"
#include <memory>

namespace test {

	class TestSandbox : public Test
	{
	public:
		TestSandbox();
		~TestSandbox();

		void OnUpdate(float deltaTime) override;
		void OnImGuiRender() override;
		void OnRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture1, m_Texture2;
	};
}
