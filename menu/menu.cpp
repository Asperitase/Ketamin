#include "menu.hpp"

namespace menu {
    void c_menu::render() const noexcept {
		static const auto manager = feature::c_manager::create();

		ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once);
		ImGui::Begin("random", nullptr, window_flags); {
			if (ImGui::BeginTabBar("##random"))
				manager->on_menu();
			ImGui::EndTabBar();
		}
		ImGui::End();

		manager->on_draw();
	}
}