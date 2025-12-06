#include "KosManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

KosManager::KosManager() : isOwnerLoggedIn(false) {
    // Load kamar dari file
    loadKamarFromFile("kamar.txt");
    
    // Load review dari file
    loadReviewFromFile("reviews.txt");
    
    // Load users
    authSystem.loadUsersFromFile("users.txt");
    // TIDAK ADA DATA DEFAULT - hanya dari file
}

bool KosManager::loginOwner() {
    std::string password;
    std::cout << "\n=== LOGIN OWNER ===" << std::endl;
    std::cout << "Password: ";
    std::cin >> password;
    
    if (authSystem.authenticateOwner(password)) {
        isOwnerLoggedIn = true;
        currentUser = "admin";
        std::cout << " Login berhasil sebagai Owner!" << std::endl;
        return true;
    }
    return false;
}

bool KosManager::loginUser() {
    std::string username, password;
    std::cout << "\n=== LOGIN USER ===" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    
    if (authSystem.authenticateUser(username, password)) {
        currentUser = username;
        std::cout << " Login berhasil sebagai " << username << "!" << std::endl;
        return true;
    }
    return false;
}

void KosManager::registerUser() {
    std::string username, password;
    std::cout << "\n=== REGISTRASI USER BARU ===" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    
    if (authSystem.registerUser(username, password)) {
        authSystem.saveUsersToFile("users.txt");
        std::cout << " Registrasi berhasil! Silakan login." << std::endl;
    } else {
        std::cout << " Username sudah digunakan!" << std::endl;
    }
}

void KosManager::mainMenu() {
    bool exitProgram = false;
    
    while (!exitProgram) {
        std::cout << "\n=========================================" << std::endl;
        std::cout << "     SISTEM MANAJEMEN KOS-KOSAN" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "1. Login sebagai Pencari Kos" << std::endl;
        std::cout << "2. Login sebagai Pemilik Kos (Owner)" << std::endl;
        std::cout << "3. Registrasi Akun Baru" << std::endl;
        std::cout << "4. Lihat Rating Kos (Tanpa Login)" << std::endl;
        std::cout << "5. Keluar" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "Pilih menu: ";
        
        int pilihan;
        std::cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                if (loginUser()) {
                    menuUser();
                }
                break;
            case 2:
                if (loginOwner()) {
                    menuOwner();
                }
                break;
            case 3:
                registerUser();
                break;
            case 4:
                tampilkanReviewKos();
                displayKosSummary();
                break;
            case 5:
                saveToFile("output.txt");
                std::cout << "Program selesai. Data tersimpan." << std::endl;
                exitProgram = true;
                break;
            default:
                std::cout << " Pilihan tidak valid!" << std::endl;
        }
    }
}

void KosManager::menuUser() {
    bool kembali = false;
    
    while (!kembali) {
        std::cout << "\n=== MENU USER ===" << std::endl;
        std::cout << "1. Lihat Kamar Tersedia" << std::endl;
        std::cout << "2. Pesan Kamar" << std::endl;
        std::cout << "3. Lihat Review Kos" << std::endl;
        std::cout << "4. Beri Review Kos" << std::endl;
        std::cout << "5. Logout" << std::endl;
        std::cout << "Pilih menu: ";
        
        int pilihan;
        std::cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                tampilkanKamarTersedia();
                break;
            case 2:
                pesanKamar();  
                break;
            case 3:
                tampilkanReviewKos();
                break;
            case 4:
                tambahReviewKos();  
                break;
            case 5:
                currentUser = "";
                std::cout << " Berhasil logout." << std::endl;
                kembali = true;
                break;
            default:
                std::cout << " Pilihan tidak valid!" << std::endl;
        }
    }
}

void KosManager::menuOwner() {
    bool kembali = false;
    
    while (!kembali) {
        std::cout << "\n=== MENU OWNER ===" << std::endl;
        std::cout << "1. Lihat Semua Kamar" << std::endl;
        std::cout << "2. Tambah Kamar Baru" << std::endl;
        std::cout << "3. Lihat Semua Review" << std::endl;
        std::cout << "4. Logout" << std::endl;
        std::cout << "Pilih menu: ";
        
        int pilihan;
        std::cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                tampilkanSemuaKamar();
                break;
            case 2:
                tambahKamar();
                break;
            case 3:
                tampilkanReviewKos();
                break;
            case 4:
                isOwnerLoggedIn = false;
                currentUser = "";
                std::cout << " Owner berhasil logout." << std::endl;
                kembali = true;
                break;
            default:
                std::cout << " Pilihan tidak valid!" << std::endl;
        }
    }
}

void KosManager::tambahKamar() {
    if (!isOwnerLoggedIn) {
        std::cout << " Akses ditolak! Hanya owner yang bisa menambah kamar." << std::endl;
        return;
    }
    
    int nomor;
    double harga;
    
    std::cout << "\n=== TAMBAH KAMAR BARU ===" << std::endl;
    std::cout << "Nomor Kamar: ";
    std::cin >> nomor;
    std::cout << "Harga per bulan: ";
    std::cin >> harga;
    
    // Cek apakah nomor kamar sudah ada
    for (const auto& kamar : daftarKamar) {
        if (kamar.getNomorKamar() == nomor) {
            std::cout << " Kamar dengan nomor " << nomor << " sudah ada!" << std::endl;
            return;
        }
    }
    
    Kamar kamarBaru(nomor, harga);
    
    // Tambah fasilitas
    std::string fasilitas;
    char tambahLagi;
    std::cin.ignore(); // Clear buffer
    
    do {
        std::cout << "Masukkan fasilitas: ";
        std::getline(std::cin, fasilitas);
        kamarBaru.tambahFasilitas(fasilitas);
        
        std::cout << "Tambah fasilitas lagi? (y/n): ";
        std::cin >> tambahLagi;
        std::cin.ignore();
    } while (tambahLagi == 'y' || tambahLagi == 'Y');
    
    daftarKamar.push_back(kamarBaru);
    simpanKamarKeFile("kamar.txt"); // Simpan ke file
    std::cout << " Kamar berhasil ditambahkan!" << std::endl;
}

void KosManager::tampilkanSemuaKamar() {
    std::cout << "\n=== DAFTAR SEMUA KAMAR ===" << std::endl;
    if (daftarKamar.empty()) {
        std::cout << "Belum ada kamar yang terdaftar." << std::endl;
    } else {
        for (const auto& kamar : daftarKamar) {
            kamar.tampilkanInfo();
        }
    }
}

void KosManager::tampilkanKamarTersedia() {
    std::cout << "\n=== KAMAR TERSEDIA ===" << std::endl;
    bool adaKamarTersedia = false;
    
    for (const auto& kamar : daftarKamar) {
        if (kamar.getStatus() == "tersedia") {
            kamar.tampilkanInfo();
            adaKamarTersedia = true;
        }
    }
    
    if (!adaKamarTersedia) {
        std::cout << " Tidak ada kamar yang tersedia saat ini." << std::endl;
    }
}

void KosManager::pesanKamar() {
    // SUDAH TIDAK PERLU CEK LOGIN - hanya bisa diakses dari menuUser
    tampilkanKamarTersedia();
    
    if (daftarKamar.empty()) {
        std::cout << "Belum ada kamar yang terdaftar." << std::endl;
        return;
    }
    
    int nomorKamar;
    std::cout << "\nPilih nomor kamar yang ingin dipesan: ";
    std::cin >> nomorKamar;
    
    Kamar* kamar = findKamarByNumber(nomorKamar);
    if (kamar) {
        if (kamar->getStatus() == "tersedia") {
            std::string nama, telepon, asal;
            
            std::cin.ignore(); // Clear buffer
            
            std::cout << "Masukkan nama lengkap: ";
            std::getline(std::cin, nama);
            
            std::cout << "Masukkan nomor telepon: ";
            std::getline(std::cin, telepon);
            
            std::cout << "Masukkan asal daerah: ";
            std::getline(std::cin, asal);
            
            kamar->setPenghuni(nama, telepon, asal);
            std::cout << "\n Kamar " << nomorKamar << " berhasil dipesan!" << std::endl;
            std::cout << "Atas nama: " << nama << std::endl;
            std::cout << "Telepon: " << telepon << std::endl;
            std::cout << "Asal: " << asal << std::endl;
            
            // Save to file immediately
            simpanKamarKeFile("kamar.txt");
            
        } else {
            std::cout << " Kamar " << nomorKamar << " sudah dipesan." << std::endl;
            std::cout << "Penghuni saat ini: " << kamar->getNamaPenghuni() << std::endl;
            std::cout << "Telepon: " << kamar->getNomorTelepon() << std::endl;
            std::cout << "Asal: " << kamar->getAsalDaerah() << std::endl;
        }
    } else {
        std::cout << " Kamar tidak ditemukan!" << std::endl;
    }
}

void KosManager::tambahReviewKos() {
    // SUDAH TIDAK PERLU CEK LOGIN - hanya bisa diakses dari menuUser
    
    int rating;
    std::string comment;
    
    std::cout << "\n=== TAMBAH REVIEW KOS ===" << std::endl;
    
    do {
        std::cout << "Berikan rating (1-5): ";
        std::cin >> rating;
        if (rating < 1 || rating > 5) {
            std::cout << "Rating harus antara 1-5!" << std::endl;
        }
    } while (rating < 1 || rating > 5);
    
    std::cin.ignore(); // Clear buffer
    std::cout << "Tulis komentar Anda: ";
    std::getline(std::cin, comment);
    
    Review reviewBaru(currentUser, rating, comment);
    daftarReview.push_back(reviewBaru);
    
    // Save to file
    reviewBaru.simpanKeFile("reviews.txt");
    
    std::cout << " Review berhasil ditambahkan!" << std::endl;
}

void KosManager::tampilkanReviewKos() {
    std::cout << "\n=== REVIEW KOS ===" << std::endl;
    
    if (daftarReview.empty()) {
        std::cout << "Belum ada review untuk kos ini." << std::endl;
        return;
    }
    
    double averageRating = Review::calculateAverageRating(daftarReview);
    std::cout << " Rata-rata Rating: " << std::fixed << std::setprecision(1) 
              << averageRating << "/5" << std::endl;
    std::cout << " Total Review: " << daftarReview.size() << std::endl;
    
    for (const auto& review : daftarReview) {
        review.displayReview();
    }
}

Kamar* KosManager::findKamarByNumber(int nomor) {
    for (auto& kamar : daftarKamar) {
        if (kamar.getNomorKamar() == nomor) {
            return &kamar;
        }
    }
    return nullptr;
}

void KosManager::displayKosSummary() const {
    std::cout << "\n=== STATISTIK KOS ===" << std::endl;
    std::cout << "Total Kamar: " << daftarKamar.size() << std::endl;
    
    int tersedia = 0;
    int dipesan = 0;
    for (const auto& kamar : daftarKamar) {
        if (kamar.getStatus() == "tersedia") tersedia++;
        else if (kamar.getStatus() == "dipesan") dipesan++;
    }
    
    std::cout << "Kamar Tersedia: " << tersedia << std::endl;
    std::cout << "Kamar Dipesan: " << dipesan << std::endl;
    std::cout << "Total Review: " << daftarReview.size() << std::endl;
}

void KosManager::loadKamarFromFile(const std::string& filename) {
    std::vector<std::string> lines = FileHandler::readLinesFromFile(filename);
    for (const auto& line : lines) {
        if (!line.empty()) {
            Kamar kamar = Kamar::bacaDariFile(line);
            daftarKamar.push_back(kamar);
        }
    }
    if (!lines.empty()) {
        std::cout << " Loaded " << daftarKamar.size() << " kamar from " << filename << std::endl;
    }
}

void KosManager::loadReviewFromFile(const std::string& filename) {
    daftarReview = Review::bacaSemuaReview(filename);
    if (!daftarReview.empty()) {
        std::cout << " Loaded " << daftarReview.size() << " reviews from " << filename << std::endl;
    }
}

void KosManager::simpanKamarKeFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc); // Clear file first
    if (file.is_open()) {
        for (const auto& kamar : daftarKamar) {
            std::ostringstream oss;
            oss << kamar.getNomorKamar() << "|" << kamar.getHarga() << "|" 
                << kamar.getStatus() << "|" << kamar.getNamaPenghuni() << "|"
                << kamar.getNomorTelepon() << "|" << kamar.getAsalDaerah() << "|";
            
            std::vector<std::string> fasilitas = kamar.getFasilitas();
            for (size_t i = 0; i < fasilitas.size(); ++i) {
                oss << fasilitas[i];
                if (i < fasilitas.size() - 1) oss << ",";
            }
            file << oss.str() << std::endl;
        }
        file.close();
    }
}

void KosManager::simpanReviewKeFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (file.is_open()) {
        for (const auto& review : daftarReview) {
            file << review.getReviewerName() << "|" 
                 << review.getRating() << "|"
                 << review.getComment() << "|"
                 << review.getDate() << std::endl;
        }
        file.close();
    }
}

void KosManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        // Implementasi loading dari file
        file.close();
        std::cout << "Data berhasil dimuat dari " << filename << std::endl;
    }
}

void KosManager::saveToFile(const std::string& filename) {
    simpanKamarKeFile("kamar.txt");
    simpanReviewKeFile("reviews.txt");
    authSystem.saveUsersToFile("users.txt");
    
    std::cout << "\n Semua data berhasil disimpan!" << std::endl;
    std::cout << "1. Kamar -> kamar.txt" << std::endl;
    std::cout << "2. Review -> reviews.txt" << std::endl;
    std::cout << "3. User -> users.txt" << std::endl;
}