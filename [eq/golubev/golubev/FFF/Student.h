#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <mutex>
#include "Grade.h"

class Student {
public:
    Student(int id, const std::string& name);

    // Конструктор копирования
    Student(const Student& other);
    // Оператор присваивания
    Student& operator=(const Student& other);
    // Конструктор перемещения
    Student(Student&& other) noexcept;
    // Оператор перемещения
    Student& operator=(Student&& other) noexcept;

    ~Student() = default;

    int getId() const;
    std::string getName() const;

    void addGrade(const Grade& grade);
    std::vector<Grade> getGradesFiltered(const std::string& semester = "", int disciplineId = -1) const;
    bool hasApprovedGrade(int disciplineId, const std::string& semester) const;
    std::vector<Grade> getGrades() const;   // возврат по значению

private:
    int m_id;
    std::string m_name;
    std::vector<Grade> m_grades;
    mutable std::mutex m_mutex;
};

#endif