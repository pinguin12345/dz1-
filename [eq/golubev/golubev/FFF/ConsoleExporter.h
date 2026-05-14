#ifndef CONSOLEEXPORTER_H
#define CONSOLEEXPORTER_H

#include "RatingExporter.h"

class ConsoleExporter : public IRatingExporter {
public:
    void exportRatings(const std::vector<RatingResult>& ratings) override;
};

#endif