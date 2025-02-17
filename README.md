# Ketamin
Game Script for Rust with GUI and safe mouse input. Compatible with the latest game update on Steam.

## Installation
To get started, clone the repository and follow the build instructions:
```bash
git clone https://github.com/Asperitase/Ketamin.git
cd Ketamin
```

## How to run project
```bash
mkdir build
cd build
cmake ..
```

## Compiling
#### Windows

* **Microsoft Visual Studio 2022 17.13 Preview 4 with flag /std:c++23preview**

Open **Ketamin.sln** in Visual Studio 2022 17.13 Preview 4 with flag /std:c++23preview, set build configuration to **Release | x64**. Press *Build solution*.

## Credits
- **[logitech-cve](https://github.com/ekknod/logitech-cve)** - Mouse movement interaction with Logitech devices.
- **[shadow_syscall](https://github.com/annihilatorq/shadow_syscall)** - Intercepting system calls.
- **[imgui/docking](https://github.com/ocornut/imgui/tree/docking)** - ImGui with docking support.
