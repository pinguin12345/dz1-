#include "CsvExporter.h"
#include <cstdio>
#include <algorithm>
#include <stdexcept>

std::string CsvExporter::escapeCsv(const std::string& field) {
    if (field.find(',') != std::string::npos || field.find('"') != std::string::npos) {
        std::string escaped = "\"";
        for (char c : field) {
            if (c == '"') escaped += "\"\"";
            else escaped += c;
        }
        escaped += "\"";
        return escaped;
    }
    return field;
}

CsvExporter::CsvExporter(const std::string& filename) : m_filename(filename) {}

void CsvExporter::exportRatings(const std::vector<RatingResult>& ratings) {
    FILE* file = fopen(m_filename.c_str(), "w");
    if (!file) {
        throw std::runtime_error("Cannot open file: " + m_filename);
    }
    fprintf(file, "Rank,ID,Name,AverageScore,TotalWeight\n");
    
    auto sorted = ratings;
    std::sort(sorted.begin(), sorted.end(),
              [](const auto& a, const auto& b) {
                  return a.averageScore > b.averageScore;
              });
    for (size_t i = 0; i < sorted.size(); ++i) {
        const auto& r = sorted[i];
        std::string escapedName = escapeCsv(r.studentName);
        fprintf(file, "%zu,%d,%s,%.2f,%.2f\n",
                i + 1, r.studentId, escapedName.c_str(), r.averageScore, r.totalWeight);
    }
    fclose(file);
}