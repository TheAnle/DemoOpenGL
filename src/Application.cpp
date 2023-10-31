#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "main", NULL, NULL);
    

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "!ok" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {

        float positions[] = {
             100.5f,  100.5f, 0.0f, 0.0f, //0
             200.5f,  100.5f, 1.0f, 0.0f, //1
             200.5f,  200.5f, 1.0f, 1.0f, //2
             100.5f,  200.5f, 0.0f, 1.0f  //3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBufer(vb, layout);


        IndexBuffer ib(indices, 6);

        //投影矩阵
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

        //视图矩阵
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));


        Shader shader("res/shader/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        

        Texture texture("res/textures/jinliu.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.UnBind();
        shader.UnBind();
        vb.UnBind();
        ib.UnBind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translation(200, 200, 0);

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            //模型矩阵
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            {                          
                ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

             /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}