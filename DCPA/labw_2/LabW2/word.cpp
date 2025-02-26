#include "word.h"
#include <QString>
#include <QVector>
Word Word::getEverythingAside(QChar symbol) {
    QString res;
    for (int i = 0; i < line.length(); i++) {
        if(line[i] != symbol) {
            res.assign(line[i]);
        }
    }
    Word result(res);
    return result;
}
QString Word::getEverythingAside(Word symbols) {

    for (int i = 0; i < line.size(); i++) {
        symbols = symbols.getEverythingAside(line[i]);
    }
    return symbols.getLine();
}
QVector <Word> Word::devideIntoUnits(QChar diviser)  {
    QVector <Word> res;
    QString temp = "";
    for (int i = 0; i < line.size(); i++ ) {
        if (line[i] == diviser) {
            Word t(temp);
            res.push_back(t);
            temp = "";
        }
        else {
            temp.assign(line[i]);
        }
    }
    if (temp != "") {
        Word t(temp);
        res.push_back(t);
    }
    return res;
}
QVector<Word> Word::getEverythingAside(QVector<Word> words) {
    QVector<Word> res;
    for(int i = 0; i < words.size(); i++) {
        if(!(this& == words[i])) {

        }
    }
}
QVector<Word> getEverythingAside(QVector<Word> words) {

}
