#include "Penghuni.h"

Penghuni::Penghuni(const std::string& nm, const std::string& telp, 
                   const std::string& asal, const std::string& tgl) {
    nama = nm;
    nomorTelepon = telp;
    asalDaerah = asal;
    tanggalMasuk = tgl;
}

std::string Penghuni::getNama() const { return nama; }
std::string Penghuni::getNomorTelepon() const { return nomorTelepon; }
std::string Penghuni::getAsalDaerah() const { return asalDaerah; }
std::string Penghuni::getTanggalMasuk() const { return tanggalMasuk; }

std::string Penghuni::getData() const {
    return "Nama: " + nama + ", Telp: " + nomorTelepon + 
           ", Asal: " + asalDaerah + ", Masuk: " + tanggalMasuk;
}