#include "Student.h"

Student::Student(int id, const std::string& name, const std::string& phone)
    : m_id(id), m_name(name), m_phone(phone) {}

int Student::getId() const { return m_id; }
std::string Student::getName() const { return m_name; }

void Student::addGrade(const Grade& grade) {
    m_grades.push_back(grade);
}

const std::vector<Grade>& Student::getGrades() const {
    return m_grades;
}

double Student::getAverageScore() const {
    if (m_grades.empty()) return 0.0;
    double sum = 0.0;

    for (const auto& g : m_grades) {
        if (g.getScore() == 0) { 
            sum += g.isPassed() ? 5.0 : 2.0;
        } else {
            sum += g.getScore();
        }
    }
    return sum / m_grades.size();
}