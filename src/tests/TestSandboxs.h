#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertBufferLayout.h"
#include "Texture.h"
#include <memory>
#include <array>

namespace test {

	class TestSandboxs : public Test
	{
	public:
		TestSandboxs();
		~TestSandboxs();

		void OnUpdate(float deltaTime) override;
		void OnImGuiRender() override;
		void OnRender() override;

	private:
		uint32_t m_Count;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture1, m_Texture2;
	};
}
