#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include <mutex>
#include "Student.h"
#include "Discipline.h"
#include "RatingCalculator.h"

class Group {
public:
    explicit Group(const std::string& name);

    // Запрещаем копирование
    Group(const Group&) = delete;
    Group& operator=(const Group&) = delete;

    // Разрешаем перемещение
    Group(Group&&) = default;
    Group& operator=(Group&&) = default;

    void addStudent(const Student& student);
    const std::string& getName() const;
    const std::vector<Student>& getStudents() const;

    void addGradeToAllStudents(int disciplineId, int score, ControlType type,
                               const std::string& semester, const std::string& date,
                               bool approved = false);
    void addGradeToAllStudents(int disciplineId, bool passed, ControlType type,
                               const std::string& semester, const std::string& date,
                               bool approved = false);

    std::vector<RatingResult> getRatedStudents(int topN,
                                               const std::vector<Discipline>& disciplines,
                                               const std::string& semester,
                                               const IGradeNormalizer* normalizer) const;

private:
    std::string m_name;
    std::vector<Student> m_students;
    mutable std::mutex m_mutex;
};

#endif