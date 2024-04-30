#include <string>

class IFileSystem {
public:
    virtual ~IFileSystem() {}

    virtual std::string getCurrentDirectory() = 0;
};

/* std::unique_ptr<IFileSystem> createFileSystem(); */
