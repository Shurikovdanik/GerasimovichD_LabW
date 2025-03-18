#ifndef APPLIEDVECTOR_H
#define APPLIEDVECTOR_H
#include "hbox.h"
class AppliedVector
{
private:
    std::pair<int, int> point;
    HBox object;
public:
    HBox move();
    AppliedVector operator+(AppliedVector another);
    AppliedVector operator*(double sc);
    AppliedVector(std::pair<int, int> point, HBox object);
};

#endif // APPLIEDVECTOR_H
