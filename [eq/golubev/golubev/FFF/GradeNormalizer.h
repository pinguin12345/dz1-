#ifndef GRADENORMALIZER_H
#define GRADENORMALIZER_H

class Grade;
class Discipline;

class IGradeNormalizer {
public:
    virtual ~IGradeNormalizer() = default;
    virtual double normalize(const Grade& grade, const Discipline& discipline) const = 0;
};

#endif