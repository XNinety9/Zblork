#include "include/LinuxFileSystem.h"
#include <unistd.h>
#include <X11/Xosdefs.h>
#include <stdexcept>
#include <limits.h>

std::string LinuxFileSystem::getCurrentDirectory() {
        char buffer[PATH_MAX];
        if (getcwd(buffer, PATH_MAX) == NULL) {
            throw std::runtime_error("Failed to get current working directory!");
        }
        return std::string(buffer);
}