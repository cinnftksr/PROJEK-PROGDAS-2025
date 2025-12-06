#ifndef KOSMANAGER_H
#define KOSMANAGER_H

#include "Kamar.h"
#include "Review.h"
#include "AuthSystem.h"
#include "FileHandler.h"
#include <vector>
#include <string>

class KosManager {
private:
    std::vector<Kamar> daftarKamar;
    std::vector<Review> daftarReview;
    AuthSystem authSystem;
    std::string currentUser;
    bool isOwnerLoggedIn;
    
public:
    KosManager();
    
    // Authentication
    bool loginOwner();
    bool loginUser();
    void registerUser();
    
    // Menu
    void mainMenu();
    void menuUser();
    void menuOwner();
    
    // Room operations
    void tambahKamar();
    void tampilkanSemuaKamar();
    void tampilkanKamarTersedia();
    void pesanKamar();
    
    // Review operations
    void tambahReviewKos();
    void tampilkanReviewKos();
    
    // File operations
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void loadKamarFromFile(const std::string& filename);
    void loadReviewFromFile(const std::string& filename);
    void simpanKamarKeFile(const std::string& filename);
    void simpanReviewKeFile(const std::string& filename);
    
    // Helper
    Kamar* findKamarByNumber(int nomor);
    void displayKosSummary() const;
};

#endif