#ifndef PENGHUNI_H
#define PENGHUNI_H

#include <string>

class Penghuni {
private:
    std::string nama;
    std::string nomorTelepon;
    std::string asalDaerah;
    std::string tanggalMasuk;

public:
    Penghuni(const std::string& nm = "", const std::string& telp = "", 
             const std::string& asal = "", const std::string& tgl = "");
    
    std::string getNama() const;
    std::string getNomorTelepon() const;
    std::string getAsalDaerah() const;
    std::string getTanggalMasuk() const;
    std::string getData() const;
};

#endif