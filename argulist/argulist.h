#ifndef ARGULIST_H
#define ARGULIST_H

#include <QStringList>

class ArgumentList : public QStringList {
    public:
        ArgumentList(int argc, char* argv[]) {
            argsToStringlist(argc, argv);
        }

        ArgumentList(const QStringList& argumentList):
            QStringList(argumentList) {}
        
        bool hasOption(char option);
        QString getOptionValue(QString option);
        QStringList getResources();
    
    private:
        void argsToStringlist(int argc,  char* argv[]);
        bool isOptionArg(const QString& arg);
};

#endif
