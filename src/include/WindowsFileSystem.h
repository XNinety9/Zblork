#include "filesystem.h"

#ifndef WINDOWSFILESYSTEM_H
#define WINDOWSFILESYSTEM_H

class WindowsFileSystem : public IFileSystem {
public:
    // Not tested 💩 🪟
    std::string getCurrentDirectory();
};

#endif /* LINUXFILESYSTEM_H */