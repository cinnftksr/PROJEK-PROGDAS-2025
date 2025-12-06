#include "Kamar.h"
#include "FileHandler.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Kamar::Kamar(int nomor, double harga) 
    : nomorKamar(nomor), harga(harga), status("tersedia"), 
      namaPenghuni("-"), nomorTelepon("-"), asalDaerah("-") {}

int Kamar::getNomorKamar() const { return nomorKamar; }
double Kamar::getHarga() const { return harga; }
std::string Kamar::getStatus() const { return status; }
std::string Kamar::getNamaPenghuni() const { return namaPenghuni; }
std::string Kamar::getNomorTelepon() const { return nomorTelepon; }
std::string Kamar::getAsalDaerah() const { return asalDaerah; }
std::vector<std::string> Kamar::getFasilitas() const { return fasilitas; }

void Kamar::setNomorKamar(int nomor) { nomorKamar = nomor; }
void Kamar::setHarga(double harga) { this->harga = harga; }
void Kamar::setStatus(const std::string& status) { this->status = status; }

void Kamar::setPenghuni(const std::string& nama, const std::string& telepon, const std::string& asal) {
    namaPenghuni = nama;
    nomorTelepon = telepon;
    asalDaerah = asal;
    status = "dipesan";
}

void Kamar::setNamaPenghuni(const std::string& nama) { namaPenghuni = nama; }
void Kamar::setNomorTelepon(const std::string& telepon) { nomorTelepon = telepon; }
void Kamar::setAsalDaerah(const std::string& asal) { asalDaerah = asal; }

void Kamar::tambahFasilitas(const std::string& fasilitas) {
    this->fasilitas.push_back(fasilitas);
}

void Kamar::tampilkanInfo() const {
    std::cout << "\nKamar " << nomorKamar << std::endl;
    std::cout << "  Harga: Rp " << std::fixed << std::setprecision(0) << harga << "/bulan" << std::endl;
    std::cout << "  Status: " << status << std::endl;
    
    if (status == "dipesan") {
        std::cout << "  Penghuni: " << namaPenghuni << std::endl;
        std::cout << "  Telepon: " << nomorTelepon << std::endl;
        std::cout << "  Asal: " << asalDaerah << std::endl;
    }
    
    std::cout << "  Fasilitas: ";
    if (fasilitas.empty()) {
        std::cout << "Tidak ada";
    } else {
        for (size_t i = 0; i < fasilitas.size(); ++i) {
            std::cout << fasilitas[i];
            if (i < fasilitas.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void Kamar::simpanKeFile(const std::string& filename) const {
    std::ostringstream oss;
    oss << nomorKamar << "|" << harga << "|" << status << "|"
        << namaPenghuni << "|" << nomorTelepon << "|" << asalDaerah << "|";
    
    for (size_t i = 0; i < fasilitas.size(); ++i) {
        oss << fasilitas[i];
        if (i < fasilitas.size() - 1) oss << ",";
    }
    
    FileHandler::saveToFile(filename, oss.str());
}

Kamar Kamar::bacaDariFile(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 6) {
        int nomor = std::stoi(tokens[0]);
        double harga = std::stod(tokens[1]);
        Kamar kamar(nomor, harga);
        
        kamar.setStatus(tokens[2]);
        kamar.setNamaPenghuni(tokens[3]);
        kamar.setNomorTelepon(tokens[4]);
        kamar.setAsalDaerah(tokens[5]);
        
        if (tokens.size() > 6 && !tokens[6].empty()) {
            std::istringstream fiss(tokens[6]);
            std::string fasilitas;
            while (std::getline(fiss, fasilitas, ',')) {
                kamar.tambahFasilitas(fasilitas);
            }
        }
        
        return kamar;
    }
    
    return Kamar(); // Return default jika error
}