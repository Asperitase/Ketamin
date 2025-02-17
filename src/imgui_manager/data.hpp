#pragma once

#include <external/ImGui/imgui.h>

struct imgui_data {
    ImFont* main_icon;
    ImFont* glory_bold;
    ImGuiIO* io;
} inline g_imgui_data;