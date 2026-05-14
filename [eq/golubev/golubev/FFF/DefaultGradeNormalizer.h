#ifndef DEFAULTGRADENORMALIZER_H
#define DEFAULTGRADENORMALIZER_H

#include "GradeNormalizer.h"

class DefaultGradeNormalizer : public IGradeNormalizer {
public:
    double normalize(const Grade& grade, const Discipline& discipline) const override;
};

#endif