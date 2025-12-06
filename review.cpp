#include "Review.h"
#include "FileHandler.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

Review::Review(const std::string& name, int rtg, 
               const std::string& cmt, const std::string& dt) {
    reviewerName = name;
    rating = (rtg < 1) ? 1 : ((rtg > 5) ? 5 : rtg);
    comment = cmt;
    
    if (dt.empty()) {
        // Generate current date if not provided
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
        date = buffer;
    } else {
        date = dt;
    }
}

std::string Review::getReviewerName() const { return reviewerName; }
int Review::getRating() const { return rating; }
std::string Review::getComment() const { return comment; }
std::string Review::getDate() const { return date; }

void Review::displayReview() const {
    std::cout << "\n=== Review ===" << std::endl;
    std::cout << "Reviewer: " << reviewerName << std::endl;
    std::cout << "Rating: " << rating << "/5" << std::endl;
    std::cout << "Komentar: " << comment << std::endl;
    std::cout << "Tanggal: " << date << std::endl;
}

void Review::simpanKeFile(const std::string& filename) const {
    std::ostringstream oss;
    oss << reviewerName << "|" << rating << "|" << comment << "|" << date;
    FileHandler::saveToFile(filename, oss.str());
}

Review Review::bacaDariFile(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 4) {
        return Review(tokens[0], std::stoi(tokens[1]), tokens[2], tokens[3]);
    }
    
    return Review(); // Return default jika error
}

std::vector<Review> Review::bacaSemuaReview(const std::string& filename) {
    std::vector<Review> reviews;
    std::vector<std::string> lines = FileHandler::readLinesFromFile(filename);
    
    for (const auto& line : lines) {
        if (!line.empty()) {
            reviews.push_back(bacaDariFile(line));
        }
    }
    
    return reviews;
}

double Review::calculateAverageRating(const std::vector<Review>& reviews) {
    if (reviews.empty()) return 0.0;
    double total = 0.0;
    for (const auto& review : reviews) {
        total += review.getRating();
    }
    return total / reviews.size();
}