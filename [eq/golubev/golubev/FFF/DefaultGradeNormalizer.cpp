#include "DefaultGradeNormalizer.h"
#include "Grade.h"
#include "Discipline.h"

double DefaultGradeNormalizer::normalize(const Grade& grade, const Discipline& discipline) const {
    if (discipline.getControlType() == ControlType::CREDIT) {
        return grade.isPassed() ? 5.0 : 2.0;
    } else {
        return static_cast<double>(grade.getScore());
    }
}