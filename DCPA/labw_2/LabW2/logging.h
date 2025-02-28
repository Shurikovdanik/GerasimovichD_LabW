#ifndef LOGGING_H
#define LOGGING_H
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QtLogging>
#include <QDateTime>
#include <QApplication>
QtMessageHandler originalHandler = nullptr;
void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message = qFormatLogMessage(type, context, msg);
    static FILE *f = fopen("logFile.txt", "a");
    fprintf(f, "%s\n", qPrintable(message));
    fflush(f);

    if (originalHandler)
        (*originalHandler)(type, context, msg);
}
void customMessageHandlerToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QFile logFile("logFile.txt");
    if (!logFile.isOpen()) {
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }

    QTextStream stream(&logFile);
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    QString message;
    switch (type) {
    case QtDebugMsg:
        message = QString("Debug: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtInfoMsg:
        message = QString("Info: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtWarningMsg:
        message = QString("Warning: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtCriticalMsg:
        message = QString("Critical: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtFatalMsg:
        message = QString("Fatal: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        abort();
    }
    stream << message << '\n';
    logFile.flush();
    fprintf(stderr, "%s\n", message.toLocal8Bit().constData());
}

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        abort();
    }
}

#endif // LOGGING_H
