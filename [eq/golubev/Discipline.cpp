#include "Discipline.h"

Discipline::Discipline(int id, const std::string& name, ControlType type, double weight)
    : m_id(id), m_name(name), m_controlType(type), m_weight(weight) {}  

int Discipline::getId() const { return m_id; }
std::string Discipline::getName() const { return m_name; }
ControlType Discipline::getControlType() const { return m_controlType; }
double Discipline::getWeight() const { return m_weight; }