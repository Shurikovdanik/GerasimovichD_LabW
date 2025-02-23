#ifndef HBOX_H
#define HBOX_H
#include <QObject>
#include <QRect>
#include "boxesoperations.h"
class HBox
{
private:
    std::pair<std::pair<int, int>, std::pair<int, int>> box;
    int mass;
    std::pair<int, int> curSpeed;
protected:
    bool haveCommonPoint(HBox other) {
        return hasMet(box, other.getBox());
    }
public:
    std::pair<std::pair<int, int>, std::pair<int, int>> getBox();
    bool operator==(HBox other) {return box == other.getBox();}
    std::pair<int, int> getCenter() {return {(box.first.first + box.second.first)/2, (box.first.second +box.second.second)/2 };}
    std::pair<int, int> getSpeed() {return curSpeed;}
    int getMass() {return mass;}
    HBox();
    HBox(std::pair<std::pair<int, int>, std::pair<int, int>> box, int mass, std::pair<int, int> speed);
};

#endif // HBOX_H
