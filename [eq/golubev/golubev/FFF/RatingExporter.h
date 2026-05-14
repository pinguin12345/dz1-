#ifndef RATINGEXPORTER_H
#define RATINGEXPORTER_H

#include <vector>
#include "RatingCalculator.h"

class IRatingExporter {
public:
    virtual ~IRatingExporter() = default;
    virtual void exportRatings(const std::vector<RatingResult>& ratings) = 0;
};

#endif