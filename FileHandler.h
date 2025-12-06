#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

class FileHandler {
public:
    static bool saveToFile(const std::string& filename, const std::string& content);
    static std::string loadFromFile(const std::string& filename);
    static std::vector<std::string> readLinesFromFile(const std::string& filename);
};

#endif