#include <iostream>
#include <vector>
#include "Student.h"
#include "Discipline.h"
#include "Grade.h"
#include "RatingCalculator.h"

int main() {
    // 1. Дисциплины
    std::vector<Discipline> disciplines;
    disciplines.emplace_back(1, "Math", ControlType::EXAM, 2.0);
    disciplines.emplace_back(2, "Physics", ControlType::EXAM, 1.5);
    disciplines.emplace_back(3, "History", ControlType::CREDIT, 1.0);

    // 2. Студенты
    Student vasya(101, "Vasya Pupkin");
    Student petya(102, "Petya Ivanov");

    // 3. Оценки
    vasya.addGrade(Grade(1, 1, 4, "spring2024", "15.05.2024"));
    vasya.addGrade(Grade(1, 2, 5, "spring2024", "20.05.2024"));
    vasya.addGrade(Grade(1, 3, true, "spring2024", "25.05.2024"));

    petya.addGrade(Grade(2, 1, 3, "spring2024", "15.05.2024"));
    petya.addGrade(Grade(2, 2, 4, "spring2024", "20.05.2024"));
    petya.addGrade(Grade(2, 3, false, "spring2024", "25.05.2024"));

    // 4. Расчёт рейтинга
    RatingResult res1 = RatingCalculator::calculateRating(vasya, disciplines, "spring2024");
    RatingResult res2 = RatingCalculator::calculateRating(petya, disciplines, "spring2024");

    std::vector<RatingResult> ratings = {res1, res2};

    // 5. Вывод
    RatingCalculator::exportRating(ratings);
    RatingCalculator::exportRatingToCSV(ratings, "rating.csv");

    return 0;
}