#include "word.h"
#include <QString>
#include <QVector>
Word Word::getEverythingAside(QChar symbol) {
    QString res = "";
    for (int i = 0; i < line.length(); i++) {
        if(line[i] != symbol) {
            res +=(line[i]);
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
            temp += (line[i]);
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
    Word th(getLine());
    for(int i = 0; i < words.size(); i++) {
        if(!(th == words[i])) {
            res.push_back(words[i]);
        }
    }
    return res;
}
QVector<Word> getEverythingAside(QVector<Word> wordsFirst, QVector<Word> wordsSecond) {
    for (int i = 0; i < wordsFirst.size(); i++) {
        wordsSecond = wordsFirst[i].getEverythingAside(wordsSecond);
    }
    for (int i = 0; i < wordsSecond.size(); i++) {
        wordsFirst = wordsSecond[i].getEverythingAside(wordsFirst);
    }
     for (int i = 0; i < wordsSecond.size(); i++) {
        wordsFirst.push_back(wordsSecond[i]);
    }
    return wordsFirst;
}
