#include <string>

class IFileSystem {
public:
    virtual ~IFileSystem() {}

    virtual std::string getCurrentDirectory() = 0;
};