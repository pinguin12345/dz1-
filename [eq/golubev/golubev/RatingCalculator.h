#ifndef RATINGCALCULATOR_H
#define RATINGCALCULATOR_H

#include <vector>
#include <string>
#include "Student.h"
#include "Discipline.h"

struct RatingResult {
    int studentId;
    std::string studentName;
    double averageScore;
    double totalWeight;
};

class RatingCalculator {
public:
    static RatingResult calculateRating(const Student& student,
                                        const std::vector<Discipline>& disciplines,
                                        const std::string& semester = "");

    static void exportRating(const std::vector<RatingResult>& ratings);
    static void exportRatingToCSV(const std::vector<RatingResult>& ratings,
                                  const std::string& filename);
};

#endif