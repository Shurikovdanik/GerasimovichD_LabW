#include "MainL.h"
#include "word.h"
const QChar SPACE = ' ';
const QChar POINT = '.';
MainL::MainL() {}
QString MainL::ex170(QString given) {
    Word cur(given);
    QVector<Word> words;
    words = cur.devideIntoUnits(SPACE);
    return (words[0].getEverythingAside(words[1]) + words[1].getEverythingAside(words[0]));
}
QString MainL::ex182(QString given) {
    Word cur(given);
    QVector<Word> words;
    words = cur.devideIntoUnits(SPACE);
    for (int i = 0; i < words.size(); i++) {
        if(words[i].firstSymbol() == 'k') {
            return words[i].getLine();
        }
    }
    return "There is no such word.";
}
QString MainL::ex194(QString given) {
    Word cur(given);
    QVector<Word> sentences;
    sentences = cur.devideIntoUnits(POINT);
    QVector<Word> wordsFirst, wordsSecond;
    wordsFirst = sentences[0].devideIntoUnits(SPACE);
    wordsSecond = sentences[1].devideIntoUnits(SPACE);
    QVector <Word> res;

}
