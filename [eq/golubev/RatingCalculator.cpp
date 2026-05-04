#include "RatingCalculator.h"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>

namespace {
    bool compareByScoreDesc(const RatingResult& a, const RatingResult& b) {
        return a.averageScore > b.averageScore;
    }
}

RatingResult RatingCalculator::calculateRating(const Student& student,
                                               const std::vector<Discipline>& disciplines,
                                               const std::string& semester) {
    double sumWeighted = 0.0;
    double totalWeight = 0.0;

    for (const Grade& grade : student.getGrades()) {
        if (!semester.empty() && grade.getSemester() != semester) {
            continue;
        }

        
        const Discipline* discPtr = nullptr;
        for (const Discipline& d : disciplines) {
            if (d.getId() == grade.getDisciplineId()) {
                discPtr = &d;
                break;
            }
        }
        if (!discPtr) continue;

        double gradeValue = 0.0;
        if (discPtr->getControlType() == ControlType::CREDIT) {
            gradeValue = grade.isPassed() ? 5.0 : 2.0;
        } else { // EXAM или COURSEWORK
            gradeValue = grade.getScore();
        }

        double weight = discPtr->getWeight();
        sumWeighted += gradeValue * weight;
        totalWeight += weight;
    }

    RatingResult res;
    res.studentId = student.getId();
    res.studentName = student.getName();
    res.averageScore = (totalWeight > 0.0) ? (sumWeighted / totalWeight) : 0.0;
    res.totalWeight = totalWeight;
    return res;
}

void RatingCalculator::exportRating(const std::vector<RatingResult>& ratings) {
    std::vector<RatingResult> sorted = ratings;
    std::sort(sorted.begin(), sorted.end(), compareByScoreDesc);

    std::cout << "RATING \n";
    std::cout << "ID\tName\t\tAvg\tTotalWeight\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& r : sorted) {
        std::cout << r.studentId << "\t"
                  << r.studentName << "\t"
                  << r.averageScore << "\t"
                  << r.totalWeight << "\n";
    }
    
}

void RatingCalculator::exportRatingToCSV(const std::vector<RatingResult>& ratings,
                                         const std::string& filename) {
    FILE* file = fopen(filename.c_str(), "w");
    if (!file) {
        std::cout << "Error: cannot open file " << filename << "\n";
        return;
    }

    fprintf(file, "ID,Name,AverageScore,TotalWeight\n");

    std::vector<RatingResult> sorted = ratings;
    std::sort(sorted.begin(), sorted.end(), compareByScoreDesc);

    for (const auto& r : sorted) {
        fprintf(file, "%d,%s,%.2f,%.2f\n",
                r.studentId,
                r.studentName.c_str(),
                r.averageScore,
                r.totalWeight);
    }

    fclose(file);
    std::cout << "CSV file saved: " << filename << "\n";
}