#include <cmath>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ren/utils/imgui.hpp"

namespace ren::utils::imgui
{
    void init(GLFWwindow* window)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
    
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void startFrame()
    {
        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    
    void endFrame()
    {
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    void terminate()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    
    void windows::hello_world(GLFWwindow* window)
    {
        // Example window
        ImGui::Begin("Hello, world!");
        ImGui::Text("This is a demo window!");
        static float f = 0.0f;
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        if (ImGui::Button("Close")) 
            glfwSetWindowShouldClose(window, true);
        ImGui::End();
    }
    
    void windows::performance_monitor(double dt)
    {
        static double curr_dt = -1;
    
        if(curr_dt == -1 || std::fabs(curr_dt - dt) > 0.001f)
        {
            curr_dt= dt;
        }
        
        if(curr_dt <= 0.00001f) return;
        double fps = 1.0 / curr_dt;
        ImGui::Begin("Performance Monitor");
        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("DeltaTime: %.4f ms", dt * 1000.0);
        ImGui::End();
    }
}

