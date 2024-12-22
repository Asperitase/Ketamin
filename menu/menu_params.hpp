#ifndef MENU_PARAMS_HPP
#define MENU_PARAMS_HPP

#include "imgui_data.hpp"

struct menu_data_t {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    int width = 600;
    int height = 300;
};

#endif // !MENU_PARAMS_HPP
