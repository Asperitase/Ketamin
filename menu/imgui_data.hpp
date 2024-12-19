#ifndef IMGUI_DATA_HPP
#define IMGUI_DATA_HPP

#include "../window/d3d/directx.hpp"

namespace imgui::data {

    struct imgui_data {
        ImFont* main_icon;
        ImFont* glory_bold;
        ImGuiIO* io;
    } inline g_imgui_data;

} // namespace imgui::data

#endif // !IMGUI_DATA_HPP
