#include "launcher/launcher.hpp"

int main(int argc, char* argv[]) {
	const auto launcher = global::c_launcher::create(argc, argv);
	return launcher ? launcher->start() : 0;
}