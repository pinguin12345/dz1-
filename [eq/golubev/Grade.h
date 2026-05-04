#ifndef GRADE_H
#define GRADE_H

#include <string>

class Grade {
public:
    // Конструктор для экзамена/курсовой 
    Grade(int studentId, int disciplineId, int score, const std::string& semester, const std::string& date);

    // Конструктор для зачёта 
    Grade(int studentId, int disciplineId, bool passed, const std::string& semester, const std::string& date);

    int getStudentId() const;
    int getDisciplineId() const;
    int getScore() const;          
    bool isPassed() const;       
    std::string getSemester() const;
    std::string getDate() const;

private:
    int m_studentId;
    int m_disciplineId;
    int m_score;       // 2-5, либо 0 если зачёт
    bool m_passed;    
    std::string m_semester;
    std::string m_date;
};

#endif