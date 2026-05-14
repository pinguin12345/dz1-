#ifndef GRADE_H
#define GRADE_H

#include <string>
#include "ControlType.h"

class Grade {
public:
    // Для экзамена/курсовой (числовая оценка 2..5)
    Grade(int studentId, int disciplineId, int score, ControlType type,
          const std::string& semester, const std::string& date, bool approved = false);
    // Для зачёта (бинарное)
    Grade(int studentId, int disciplineId, bool passed, ControlType type,
          const std::string& semester, const std::string& date, bool approved = false);

    int getStudentId() const;
    int getDisciplineId() const;
    int getScore() const;
    bool isPassed() const;
    ControlType getControlType() const;
    std::string getSemester() const;
    std::string getDate() const;
    bool isApproved() const;
    void setApproved(bool approved);

private:
    int m_studentId;
    int m_disciplineId;
    int m_score;          // для экзамена/курсовой
    bool m_passed;        // для зачёта
    ControlType m_controlType;
    std::string m_semester;
    std::string m_date;
    bool m_approved;
};

#endif