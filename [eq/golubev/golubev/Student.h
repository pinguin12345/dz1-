#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Grade.h"

class Student {
public:
    Student(int id, const std::string& name, const std::string& phone = "");

    int getId() const;
    std::string getName() const;
    double getAverageScore() const;
    void addGrade(const Grade& grade);
    const std::vector<Grade>& getGrades() const;

private:
    int m_id;
    std::string m_name;
    std::string m_phone;
    std::vector<Grade> m_grades;
};

#endif