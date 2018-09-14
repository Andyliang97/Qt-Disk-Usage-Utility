#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "diskusage.h"

DiskUsage::DiskUsage(int depth, UnitSize size, ResourceType type)
{
    if (size <= 0 || depth < -1) 
    {
        qDebug() << "Wrong argument" << endl; 
        return;
    }
    mDepth = depth;
    mSize = size;
    mType = type;
}
    
QString DiskUsage::formatSize(int size)
{
    if (mSize == SIZE_KB)
		size = size / 1024 + ((size % 1024 == 0) ? 0 : 1); 
    if (mSize == SIZE_MB)
        size = size / (1024 * 1024) + ((size % (1024 * 1024) == 0) ? 0 : 1);
    QString num = QString::number(size);
    if (mSize == SIZE_KB)
        num += " kB";
    else if (mSize == SIZE_MB)
        num += " MB";
    else 
        num += " B";
    return num;
}

void DiskUsage::recurseProcess(QFileInfo file, int depth, QStringList& result)
{
	if ( ((mType & (1 << TYPE_FILE)) && file.isFile() && !file.isSymLink()) || 
		 ((mType & (1 << TYPE_DIR)) && file.isDir() && !file.isSymLink()) ||  
		 ((mType & (1 << TYPE_SYM)) && file.isSymLink()) )  
		result << formatSize(getFileSize(file)) << file.filePath(); 

    if (depth <= 0 || file.isFile() || file.isSymLink())
        return;

    QDir d(file.filePath());
    d.setSorting(QDir::Name);
    QDir::Filters df = QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs;
    foreach (const QFileInfo &entry, d.entryInfoList(df, QDir::Name)) 
    {
        recurseProcess(entry, depth - 1, result);
    }
}

QStringList DiskUsage::process(QStringList resources)
{
    resources.sort();
    QStringList result;
    for (int i = 0; i < resources.size(); ++ i)
    {
        recurseProcess(QFileInfo(resources.at(i)), mDepth, result);
    }
    return result;
}

int DiskUsage::getFileSize(QFileInfo file)
{
    if (file.isFile())
    {
        return file.size();
    }
    else if (file.isSymLink())
    {
        QFileInfo target(file.symLinkTarget());
        return target.size();
    }
    else 
    {
        int size = file.size();
        QDir d(file.filePath());
        QDir::Filters df = QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs;
        foreach (const QFileInfo &entry, d.entryInfoList(df, QDir::Name)) 
            size += getFileSize(entry);
        return size;
    }
    return 0;
}

