#ifndef KAMAR_H
#define KAMAR_H

#include <string>
#include <vector>

class Kamar {
private:
    int nomorKamar;
    double harga;
    std::string status;
    std::string namaPenghuni;
    std::string nomorTelepon;
    std::string asalDaerah;
    std::vector<std::string> fasilitas;
    
public:
    Kamar(int nomor = 0, double harga = 0.0);
    
    // Getter methods
    int getNomorKamar() const;
    double getHarga() const;
    std::string getStatus() const;
    std::string getNamaPenghuni() const;
    std::string getNomorTelepon() const;
    std::string getAsalDaerah() const;
    std::vector<std::string> getFasilitas() const;
    
    // Setter methods
    void setNomorKamar(int nomor);
    void setHarga(double harga);
    void setStatus(const std::string& status);
    void setPenghuni(const std::string& nama, const std::string& telepon = "", const std::string& asal = "");
    void setNamaPenghuni(const std::string& nama);
    void setNomorTelepon(const std::string& telepon);
    void setAsalDaerah(const std::string& asal);
    
    void tambahFasilitas(const std::string& fasilitas);
    void tampilkanInfo() const;
    void simpanKeFile(const std::string& filename) const;
    static Kamar bacaDariFile(const std::string& line);
};

#endif