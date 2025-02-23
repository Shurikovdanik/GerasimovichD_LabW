#include "hbox.h"

HBox::HBox() {}
HBox::HBox(std::pair<std::pair<int, int>, std::pair<int, int>> box, int mass, std::pair<int, int> speed) {
    this -> box = box;
    this -> mass = mass;
    this -> curSpeed = speed;
}
std::pair<std::pair<int, int>, std::pair<int, int>> HBox::getBox() {
    return box;
}
