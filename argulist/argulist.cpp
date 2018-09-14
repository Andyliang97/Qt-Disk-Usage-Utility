
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include "argulist.h"

void ArgumentList::argsToStringlist(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        *this += argv[i];
    }
}

bool ArgumentList::isOptionArg(const QString& arg) {
    return arg[0] == '-';
}

bool ArgumentList::hasOption(char option) {
    for (int i = 0; i < size(); ++i) {
        QString tmpArg = at(i);
        if (! isOptionArg(tmpArg))  // meet the argument which is not option argument 
            continue;
        QString content = tmpArg.mid(1);
        if (content.indexOf('=') >= 0) // another format of option 
            continue;
        if (content.indexOf(option) >= 0)
            return true;
    }
    return false;
}

QString ArgumentList::getOptionValue(QString option) {
    for (int i = 0; i < size(); ++i) {
        QString tmpArg = at(i);
        if (! isOptionArg(tmpArg))  // meet the argument which is not option argument 
            continue;
        QString content = tmpArg.mid(1);
        int index = content.indexOf('=');
        if (index < 0) // another format of option 
            continue;
        QString key = content.mid(0, index);
        QString value = content.mid(index + 1);
        if (key != option)
            continue;
        return value;
    }
    return QString();
}

QStringList ArgumentList::getResources() {
    QStringList l;
    for (int i = 0; i < size(); ++i) {
        QString tmpArg = at(i);
        if (isOptionArg(tmpArg)) 
            continue;
        l << tmpArg;
    }
    return l;
}


