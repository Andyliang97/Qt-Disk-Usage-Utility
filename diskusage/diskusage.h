#ifndef DISKUSAGE_H
#define DISKUSAGE_H

#include <QString>
#include <QStringList>
#include <QFileInfo>

#define MAX_DEPTH 1024

enum 
{
    SIZE_BYTE = 1,
    SIZE_KB,
    SIZE_MB,
};

enum 
{
    TYPE_FILE,
    TYPE_DIR,
    TYPE_SYM,
};

typedef int UnitSize;
typedef int ResourceType;

class DiskUsage 
{
public:
    DiskUsage(int depth, UnitSize size, ResourceType type);
    
    QStringList process(QStringList resources);

private:
    int mDepth;
    UnitSize mSize;
    ResourceType mType;
    
    QString formatSize(int size);
    
    int getFileSize(QFileInfo file);

    void recurseProcess(QFileInfo file, int depth, QStringList& result);
};

#endif 

