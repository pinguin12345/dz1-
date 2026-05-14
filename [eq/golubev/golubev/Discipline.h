#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <string>

enum class ControlType {
    EXAM,
    CREDIT,
    COURSEWORK
};

class Discipline {
public:
    Discipline(int id, const std::string& name, ControlType type, double weight = 1.0);

    int getId() const;
    std::string getName() const;
    ControlType getControlType() const;
    double getWeight() const;

private:
    int m_id;
    std::string m_name;
    ControlType m_controlType;   // исправил имя поля
    double m_weight;
};

#endif