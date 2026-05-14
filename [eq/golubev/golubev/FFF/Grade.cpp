#include "Grade.h"
#include <stdexcept>

static void validateScore(int score, ControlType type) {
    if (type == ControlType::EXAM || type == ControlType::COURSEWORK) {
        if (score < 2 || score > 5)
            throw std::invalid_argument("Score must be between 2 and 5 for exam/coursework");
    }
}

Grade::Grade(int studentId, int disciplineId, int score, ControlType type,
             const std::string& semester, const std::string& date, bool approved)
    : m_studentId(studentId), m_disciplineId(disciplineId), m_score(score),
      m_passed(score >= 3), m_controlType(type), m_semester(semester),
      m_date(date), m_approved(approved)
{
    validateScore(score, type);
}

Grade::Grade(int studentId, int disciplineId, bool passed, ControlType type,
             const std::string& semester, const std::string& date, bool approved)
    : m_studentId(studentId), m_disciplineId(disciplineId), m_score(0),
      m_passed(passed), m_controlType(type), m_semester(semester),
      m_date(date), m_approved(approved)
{
    if (type != ControlType::CREDIT)
        throw std::invalid_argument("Boolean grade allowed only for CREDIT control type");
}

int Grade::getStudentId() const { return m_studentId; }
int Grade::getDisciplineId() const { return m_disciplineId; }
int Grade::getScore() const { return m_score; }
bool Grade::isPassed() const { return m_passed; }
ControlType Grade::getControlType() const { return m_controlType; }
std::string Grade::getSemester() const { return m_semester; }
std::string Grade::getDate() const { return m_date; }
bool Grade::isApproved() const { return m_approved; }
void Grade::setApproved(bool approved) { m_approved = approved; }