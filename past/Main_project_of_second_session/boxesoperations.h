#ifndef BOXESOPERATIONS_H
#define BOXESOPERATIONS_H
#include <QPair>
bool hasMet(std::pair<std::pair<int, int>, std::pair<int, int>> first, std::pair<std::pair<int, int>, std::pair<int, int>> second);
bool isInBox(std::pair <int, int> point, std::pair<std::pair<int, int>, std::pair<int, int>> box);
#endif // BOXESOPERATIONS_H
