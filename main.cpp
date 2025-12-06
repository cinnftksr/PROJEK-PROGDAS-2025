#include <iostream>
#include "KosManager.h"

int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "   PROGRAM MANAJEMEN KOS-KOSAN 2024" << std::endl;
    std::cout << "   Universitas Gadjah Mada" << std::endl;
    std::cout << "   Mata Kuliah: Pemrograman Dasar" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    KosManager sistem;
    sistem.mainMenu();
    
    return 0;
}