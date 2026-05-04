#include "Grade.h"

// экзамен / курсовая
Grade::Grade(int studentId, int disciplineId, int score, const std::string& semester, const std::string& date)
    : m_studentId(studentId), m_disciplineId(disciplineId), m_score(score),
      m_passed(score >= 3),
      m_semester(semester), m_date(date) {}

// зачёт
Grade::Grade(int studentId, int disciplineId, bool passed, const std::string& semester, const std::string& date)
    : m_studentId(studentId), m_disciplineId(disciplineId), m_score(0),
      m_passed(passed),
      m_semester(semester), m_date(date) {}

int Grade::getStudentId() const { return m_studentId; }
int Grade::getDisciplineId() const { return m_disciplineId; }
int Grade::getScore() const { return m_score; }
bool Grade::isPassed() const { return m_passed; }
std::string Grade::getSemester() const { return m_semester; }
std::string Grade::getDate() const { return m_date; }