#include "include/WindowsFileSystem.h"

#include "filesystem.h"
#include <stdexcept>

// Todo test, aka not my problem
std::string WindowsFileSystem::getCurrentDirectory() {
        char buffer[MAX_PATH];
        DWORD size = GetCurrentDirectoryA(buffer, MAX_PATH);
        if (size == 0) {
            throw std::runtime_error("Failed to get current working directory");
        }
        return std::string(buffer);
}
