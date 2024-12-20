#include "menu.hpp"

namespace menu {
    void c_menu::render() const noexcept {
		ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once);
		ImGui::Begin("random", nullptr, window_flags); {
			if (ImGui::BeginTabBar("##random"))
				feature::c_manager::instance().on_menu();
			ImGui::EndTabBar();
		}
		ImGui::End();
		feature::c_manager::instance().on_draw();
	}
}