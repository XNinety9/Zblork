
#ifndef LINUXFILESYSTEM_H
#define LINUXFILESYSTEM_H

#include "filesystem.h"

class LinuxFileSystem : public IFileSystem {
public:
    ~LinuxFileSystem() {}

    std::string getCurrentDirectory();
};

#endif /* LINUXFILESYSTEM_H */