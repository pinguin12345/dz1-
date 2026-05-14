#include "ConsoleExporter.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void ConsoleExporter::exportRatings(const std::vector<RatingResult>& ratings) {
    auto sorted = ratings;
    std::sort(sorted.begin(), sorted.end(),
              [](const auto& a, const auto& b) {
                  return a.averageScore > b.averageScore;
              });
    // Проставляем места
    for (size_t i = 0; i < sorted.size(); ++i) {
        const_cast<RatingResult&>(sorted[i]).rankPosition = static_cast<int>(i + 1);
    }
    
    std::cout << "=================================\n";
    std::cout << "          STUDENT RATING          \n";
    std::cout << "=================================\n";
    std::cout << "Pos\tID\tName\t\tAvg\tWeight\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& r : sorted) {
        std::cout << r.rankPosition << "\t"
                  << r.studentId << "\t"
                  << r.studentName << "\t"
                  << r.averageScore << "\t"
                  << r.totalWeight << "\n";
    }
}