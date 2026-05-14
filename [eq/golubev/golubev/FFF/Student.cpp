
#include "Student.h"
#include <algorithm>
#include <stdexcept>
#include <utility>   // для std::exchange

Student::Student(int id, const std::string& name) : m_id(id), m_name(name) {}

// Конструктор копирования: копируем поля, мьютекс создаётся новый
Student::Student(const Student& other)
    : m_id(other.m_id), m_name(other.m_name), m_grades(other.m_grades)
{
    // мьютекс инициализируется по умолчанию (новый)
}

// Оператор присваивания
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        m_id = other.m_id;
        m_name = other.m_name;
        m_grades = other.m_grades;
        // мьютекс остаётся своим, не копируется
    }
    return *this;
}

// Конструктор перемещения
Student::Student(Student&& other) noexcept
    : m_id(std::exchange(other.m_id, 0)),
      m_name(std::move(other.m_name)),
      m_grades(std::move(other.m_grades))
{
    // мьютекс нового объекта создаётся автоматически, не перемещается
}

// Оператор перемещения
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        m_id = std::exchange(other.m_id, 0);
        m_name = std::move(other.m_name);
        m_grades = std::move(other.m_grades);
    }
    return *this;
}

int Student::getId() const { return m_id; }
std::string Student::getName() const { return m_name; }

bool Student::hasApprovedGrade(int disciplineId, const std::string& semester) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = std::find_if(m_grades.begin(), m_grades.end(),
        [disciplineId, &semester](const Grade& g) {
            return g.getDisciplineId() == disciplineId &&
                   g.getSemester() == semester &&
                   g.isApproved();
        });
    return it != m_grades.end();
}

void Student::addGrade(const Grade& grade) {
    if (grade.isApproved()) {
        if (hasApprovedGrade(grade.getDisciplineId(), grade.getSemester())) {
            throw std::logic_error("Approved grade already exists for this discipline and semester");
        }
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    m_grades.push_back(grade);
}

std::vector<Grade> Student::getGradesFiltered(const std::string& semester, int disciplineId) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<Grade> result;
    for (const auto& g : m_grades) {
        if (!semester.empty() && g.getSemester() != semester) continue;
        if (disciplineId != -1 && g.getDisciplineId() != disciplineId) continue;
        result.push_back(g);
    }
    return result;
}

std::vector<Grade> Student::getGrades() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_grades;   // возвращаем копию
}