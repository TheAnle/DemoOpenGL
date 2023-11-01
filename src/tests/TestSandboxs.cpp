#include "TestSandboxs.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	struct DrawData
	{
		float Position[3];
		float Color[4];
		float TexCoords[2];
		float TextureID;
	};

	static DrawData* CreateQuad(DrawData* target,float x, float y, float textureID)
	{
		float size = 100.0f;

		*target = { {x, y, 0.0f}, {0.18f, 0.6f, 0.96f, 1.0f}, {0.0f, 0.0f}, textureID };
		target++;

		*target = { {x + size, y, 0.0f}, {0.18f, 0.6f, 0.96f, 1.0f}, {1.0f, 0.0f}, textureID };
		target++;

		*target = { {x + size, y + size, 0.0f}, {0.18f, 0.6f, 0.96f, 1.0f}, {1.0f, 1.0f}, textureID };
		target++;

		*target = { {x, y + size, 0.0f}, {0.18f, 0.6f, 0.96f, 1.0f}, {0.0f, 1.0f}, textureID };
		target++;

		return target;
	}

	TestSandboxs::TestSandboxs()
	{

		float positions[] = {
			 100.5f,  100.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 0.0f,  //0
			 200.5f,  100.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 0.0f, //1
			 200.5f,  200.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 0.0f, //2
			 100.5f,  200.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 0.0f,  //3
							  
			 300.5f,  100.5f, 0.0f,	1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 0.0f, 1.0f, //4
			 400.5f,  100.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 0.0f, 1.0f, //5
			 400.5f,  200.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 1.0f, 1.0f, //6
			 300.5f,  200.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 1.0f, 1.0f //7
		};
		std::array<DrawData, 2> positionss;
		DrawData* draw = positionss.data();

		
		//auto p0 = CreateQuad(draw, 100.0f, 100.0f, 0.0f);
		//auto p1 = CreateQuad(draw, 300.0f, 100.0f, 1.0f);


		unsigned int indicesr[] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4
		};
		const unsigned int length = 12;
		unsigned int offset = 0;
		unsigned int indices[length];
		for (size_t i = 0; i < length; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		m_VAO = std::make_unique<VertexArray>();

		//m_VertexBuffer = std::make_unique<VertexBuffer>(positions.data(), sizeof(DrawData) * positions.size(), 1);
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));


		VertBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);

		m_VAO->AddBufer(*m_VertexBuffer, layout);


		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, length);



		m_Shader = std::make_unique<Shader>("res/shader/box.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		int sam[2] = { 0,1 };
		m_Shader->SetUniform1iv("u_Textures", 2, sam);

		m_Texture1 = std::make_unique<Texture>("res/textures/jinliu.png");
		m_Texture2 = std::make_unique<Texture>("res/textures/yinglang.png");
		//m_Shader->SetUniform1i("a_TexIndex", 0);
	}

	TestSandboxs::~TestSandboxs()
	{
	}


	void TestSandboxs::OnUpdate(float deltaTime)
	{


	}

	void TestSandboxs::OnRender()
	{
		glm::vec3 m_TranslationA(200, 200, 0);
		GLCall(glClearColor(1.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture1->Bind(0);
		m_Texture2->Bind(1);

		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);

		glm::mat4 vp = proj * view;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_ViewProj", vp);


		m_Shader->SetUniformMat4f("u_Transform", model);

		//m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);


	}

	void TestSandboxs::OnImGuiRender()
	{
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}