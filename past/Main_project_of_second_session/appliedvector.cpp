#include "appliedvector.h"

AppliedVector::AppliedVector(std::pair<int, int> point, HBox object) {
    this -> point = point;
    this->object = object;
}
AppliedVector AppliedVector::operator+(AppliedVector other) {
    if(object == other.object) {
        std::pair<int, int> sum = {point.first + other.point.first, point.second + other.point.second};
        AppliedVector res (sum, object);
        return res;
    }
    else throw ("Sum of vectors applied to different objects.");
}
HBox AppliedVector::move() {
    std::pair<std::pair<int, int>, std::pair<int, int>> box = this->object.getBox();
    std::pair<int, int> speed = object.getSpeed();
    int xIncr = speed.first - ((point.first) / object.getMass());
    int yIncr = speed.second - ((point.second) / object.getMass());
    //std::pair<std::pair<int, int>, std::pair<int, int>> resBox = {};
    box = {{box.first.first+xIncr, box.first.second+yIncr},{box.second.first+xIncr, box.second.second+yIncr}};
    HBox res(box, object.getMass(), {xIncr, yIncr});
}
