#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include "RatingExporter.h"
#include <string>

class CsvExporter : public IRatingExporter {
public:
    explicit CsvExporter(const std::string& filename);
    void exportRatings(const std::vector<RatingResult>& ratings) override;
private:
    std::string m_filename;
    static std::string escapeCsv(const std::string& field);
};

#endif