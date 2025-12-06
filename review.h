#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include <vector>

class Review {
private:
    std::string reviewerName;
    int rating;
    std::string comment;
    std::string date;
    
public:
    Review(const std::string& name = "", int rtg = 0, 
           const std::string& cmt = "", const std::string& date = "");
    
    std::string getReviewerName() const;
    int getRating() const;
    std::string getComment() const;
    std::string getDate() const;
    
    void displayReview() const;
    void simpanKeFile(const std::string& filename) const;
    static Review bacaDariFile(const std::string& line);
    static std::vector<Review> bacaSemuaReview(const std::string& filename);
    static double calculateAverageRating(const std::vector<Review>& reviews);
};

#endif