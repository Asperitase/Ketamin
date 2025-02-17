#ifndef IMGUI_DATA_HPP
#define IMGUI_DATA_HPP

#include "imgui.h"

namespace imgui::data {

    struct imgui_data {
        ImFont* main_icon;
        ImFont* glory_bold;
        ImGuiIO* io;
    } inline g_imgui_data;

} // namespace imgui::data

#endif // !IMGUI_DATA_HPP
