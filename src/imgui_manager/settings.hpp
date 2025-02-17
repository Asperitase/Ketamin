#pragma once

#include <external/ImGui/imgui.h>

struct menu_settings {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    int width = 810;
    int height = 510;
};