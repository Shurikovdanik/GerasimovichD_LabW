#ifndef WORD_H
#define WORD_H
#include <QString>
#include <QVector>
class Word
{
private:
    QString line;
public:
    QString getLine() {return line;}
    Word getEverythingAside(QChar symbol);
    QVector<Word> getEverythingAside(QVector<Word> words);
    QString getEverythingAside(Word symbols);
    QChar firstSymbol() {return line[0];}
    QVector <Word> devideIntoUnits(QChar diviser);
    Word(QString line) {this -> line = line;}
    bool operator==(Word other) {return line == other.getLine();}
};
QVector<Word> getEverythingAside(QVector<Word> wordsFirst, QVector<Word> wordsSecond);
#endif // WORD_H
