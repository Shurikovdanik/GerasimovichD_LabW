#include "boxesoperations.h"
bool hasMet(std::pair<std::pair<int, int>, std::pair<int, int>> first, std::pair<std::pair<int, int>, std::pair<int, int>> second) {
    bool firstType = isInBox(first.first, second);
    bool secondType = isInBox(second.first, first);
    bool thirdType = isInBox(second.second, first);
    bool fourthType = isInBox(first.second, second);
    return (firstType ^ secondType ^ thirdType ^ fourthType);
}
bool isInBox(std::pair <int, int> point, std::pair<std::pair<int, int>, std::pair<int, int>> box) {
    bool firstType = (point.first < box.second.first && point.second < box.second.second && point.first > box.first.first && point.second > box.first.second);
    bool secondType = (point.first > box.second.first && point.second > box.second.second && point.first < box.first.first && point.second < box.first.second);
    return (firstType ^ secondType);
}
