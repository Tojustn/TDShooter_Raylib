#include "raylib.h"
#include <iostream>

#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion

int main(void)
{
	const int screenWidth = 750;
	const int screenHeight = 750;
	// Checks the last time the snake has moved
	bool showImGUI = true;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	SetTargetFPS(60);

#pragma region imgui
	rlImGuiSetup(true);

	//you can use whatever imgui theme you like!
	//ImGui::StyleColorsDark();
	//imguiThemes::yellow();
	//imguiThemes::gray();
	//imguiThemes::green();
	//imguiThemes::red();
//
//	imguiThemes::embraceTheDarkness();
//
//
//	ImGuiIO& io = ImGui::GetIO(); (void)io;
//	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
//	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
//	io.FontGlobalScale = 2;
//
//	ImGuiStyle& style = ImGui::GetStyle();
//	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//	{
//		//style.WindowRounding = 0.0f;
//		style.Colors[ImGuiCol_WindowBg].w = 0.5f;
//		//style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
//	}
//
#pragma endregion
	while (!WindowShouldClose())
	{
		ClearBackground(BLACK);


//
//#pragma region imgui
//			rlImGuiBegin();
//
//			ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
//			ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
//			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
//			ImGui::PopStyleColor(2);
//#pragma endregion
//
//
//			ImGui::Begin("Test");
//			ImGui::End();
//#pragma region imgui
//			rlImGuiEnd();
//
//			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//			{
//				ImGui::UpdatePlatformWindows();
//				ImGui::RenderPlatformWindowsDefault();
//			}
//#pragma endregion
//
//		}
//		EndDrawing();
//
//
//#pragma region imgui
//	rlImGuiShutdown();
//#pragma endregion
//
//
//
	CloseWindow();

	return 0;
}



