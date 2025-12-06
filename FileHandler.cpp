#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool FileHandler::saveToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::app); // Mode append
    if (file.is_open()) {
        file << content << std::endl;
        file.close();
        return true;
    }
    std::cerr << "Error: Tidak bisa membuka file " << filename << " untuk ditulis" << std::endl;
    return false;
}

std::string FileHandler::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
    } else {
        std::cerr << "Error: Tidak bisa membuka file " << filename << " untuk dibaca" << std::endl;
    }
    return buffer.str();
}

std::vector<std::string> FileHandler::readLinesFromFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Tidak bisa membuka file " << filename << std::endl;
    }
    return lines;
}