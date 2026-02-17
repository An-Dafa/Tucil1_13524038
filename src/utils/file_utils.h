#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

std::vector<std::string> readInputFile(const std::string& filename);

void saveSolution(const std::string& filename,  const std::vector<std::string>& gridData, long long timeMs, long long cases, const std::string& algo);

#endif