#include <QDateTime>
#include "MainL.h"
#include <QtLogging>
#include "word.h"
#include "logging.h"
const QChar SPACE = ' ';
const QChar POINT = '.';

MainL::MainL() {}
QString MainL::ex170(QString given) {
    originalHandler = qInstallMessageHandler(logToFile);
    qDebug() << "Debug: task 170 running";
    Word cur(given);
    QVector<Word> words;
    words = cur.devideIntoUnits(SPACE);
    qInfo() << "Info: task 170 is continued: " << words[0].getLine() << ", " << words[1].getLine();
    qDebug() << "Debug: task 170 finished";
    return (words[0].getEverythingAside(words[1]) + words[1].getEverythingAside(words[0]));
}
QString MainL::ex182(QString given) {
    originalHandler = qInstallMessageHandler(logToFile);
    Word cur(given);
    QVector<Word> words;
    qDebug() << "Debug: task 182 running";
    words = cur.devideIntoUnits(SPACE);
    qInfo() << "Info: task 182 is continued ";
    for (int i = 0; i < words.size(); i++) {
        qInfo() << words[i].getLine() << " ";
    }
    for (int i = 0; i < words.size(); i++) {
        if(words[i].firstSymbol() == 'k') {
             qDebug() << "Debug: task 182 finished";
            return words[i].getLine();
        }
    }
    qDebug() << "Debug: task 182 finished";
    return "There is no such word.";
}
QString MainL::ex194(QString given) {
    Word cur(given);
    QVector<Word> sentences;
     qDebug() << "Debug: task 182 running";
    sentences = cur.devideIntoUnits(POINT);
     qInfo() << "Info: task 182 is continued ";
     for (int i = 0; i < sentences.size(); i++) {
         qInfo() << sentences[i].getLine() << " ";
     }
    QVector<Word> wordsFirst, wordsSecond;
    wordsFirst = sentences[0].devideIntoUnits(SPACE);
    qInfo() << "Info: task 182 is continued ";
    for (int i = 0; i < wordsFirst.size(); i++) {
        qInfo() << wordsFirst[i].getLine() << " ";
    }
    wordsSecond = sentences[1].devideIntoUnits(SPACE);
    qInfo() << "Info: task 182 is continued ";
    for (int i = 0; i < wordsSecond.size(); i++) {
        qInfo() << wordsSecond[i].getLine() << " ";
    }
    QVector <Word> res = getEverythingAside(wordsFirst, wordsSecond);
    QString result = "";
    for (int i = 0; i < res.size(); i++) {
        result += res[i].getLine();
        result += " ";
    }
    return result;
}
