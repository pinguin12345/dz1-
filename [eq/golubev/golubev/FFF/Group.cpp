#include "Group.h"
#include <algorithm>
#include <stdexcept>

Group::Group(const std::string& name) : m_name(name) {}

void Group::addStudent(const Student& student) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_students.push_back(student);
}

const std::string& Group::getName() const { return m_name; }
const std::vector<Student>& Group::getStudents() const { return m_students; }

void Group::addGradeToAllStudents(int disciplineId, int score, ControlType type,
                                  const std::string& semester, const std::string& date,
                                  bool approved) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& student : m_students) {
        Grade grade(student.getId(), disciplineId, score, type, semester, date, approved);
        student.addGrade(grade);
    }
}

void Group::addGradeToAllStudents(int disciplineId, bool passed, ControlType type,
                                  const std::string& semester, const std::string& date,
                                  bool approved) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& student : m_students) {
        Grade grade(student.getId(), disciplineId, passed, type, semester, date, approved);
        student.addGrade(grade);
    }
}

std::vector<RatingResult> Group::getRatedStudents(int topN,
                                                  const std::vector<Discipline>& disciplines,
                                                  const std::string& semester,
                                                  const IGradeNormalizer* normalizer) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    RatingCalculator calculator(normalizer);
    std::vector<RatingResult> ratings;
    for (const auto& student : m_students) {
        RatingResult res = calculator.calculate(student, disciplines, semester);
        ratings.push_back(res);
    }
    std::sort(ratings.begin(), ratings.end(),
              [](const RatingResult& a, const RatingResult& b) {
                  return a.averageScore > b.averageScore;
              });
    for (size_t i = 0; i < ratings.size(); ++i) {
        ratings[i].rankPosition = static_cast<int>(i + 1);
    }
    if (topN > 0 && static_cast<size_t>(topN) < ratings.size()) {
        ratings.resize(topN);
    }
    return ratings;
}