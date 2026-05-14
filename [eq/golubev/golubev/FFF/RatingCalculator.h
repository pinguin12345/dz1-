#ifndef RATINGCALCULATOR_H
#define RATINGCALCULATOR_H

#include <vector>
#include <string>
#include "GradeNormalizer.h"
#include "Student.h"
#include "Discipline.h"

struct RatingResult {
    int studentId;
    std::string studentName;
    double averageScore;
    double totalWeight;      // суммарный вес (аналог total_credits)
    int rankPosition = 0;    // FR-06, FR-07
};

class RatingCalculator {
public:
    explicit RatingCalculator(const IGradeNormalizer* normalizer);
    
    // Старый метод для совместимости (фильтр по семестру)
    RatingResult calculate(const Student& student,
                           const std::vector<Discipline>& disciplines,
                           const std::string& semester = "") const;
    
    // FR-07: расчёт по датам
    RatingResult calculateRating(int studentId,
                                 const std::string& startDate,
                                 const std::string& endDate,
                                 const std::vector<Discipline>& disciplines,
                                 const std::vector<Student>& students) const;
    
    // Вспомогательный метод для вычисления позиции в общем списке
    static int getRankPosition(int studentId,
                               const std::vector<RatingResult>& allRatings);
private:
    const IGradeNormalizer* m_normalizer;
    
    // Общая логика расчёта по оценкам
    RatingResult computeFromGrades(const Student& student,
                                   const std::vector<Grade>& grades,
                                   const std::vector<Discipline>& disciplines) const;
};

#endif