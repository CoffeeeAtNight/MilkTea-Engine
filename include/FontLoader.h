#pragma once

#include <imgui.h>

class FontLoader
{
public:
	FontLoader();
	~FontLoader();


private:
	ImGuiIO& io = ImGui::GetIO();
	ImFont* _mGuiFont = io.Fonts->AddFontFromFileTTF("", 15.5);
	//TODO()
};