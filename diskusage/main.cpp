#include <QString>
#include <QDebug>
#include <QTextStream>
#include <argulist.h>
#include <stdlib.h>
#include "diskusage.h"

void Usage()
{
    qDebug() << "./diskusage -depth=(all|<uint>) (-b|-k|-m) -<type> resource0 [resource1 [...]]" << endl;
    exit(0);
}

int main( int argc, char * argv[])
{
    ArgumentList al(argc, argv);
    
    int depth = 0;
    QString sDepth = al.getOptionValue("depth");
    bool ok = true;
    if (sDepth == "all")
        depth = MAX_DEPTH; 
    else 
        depth = sDepth.toInt(&ok, 10); 
    
    UnitSize size = 0;
    if (al.hasOption('b'))
        size = SIZE_BYTE;
    if (al.hasOption('k'))
        size = SIZE_KB;
    if (al.hasOption('m'))
        size = SIZE_MB;
    
    ResourceType type = 0;
    if (al.hasOption('f'))
        type |= (1 << TYPE_FILE);
    if (al.hasOption('d'))
        type |= (1 << TYPE_DIR);
    if (al.hasOption('s'))
        type |= (1 << TYPE_SYM);
    
    QStringList resources = al.getResources(); 
    if (!ok || depth < 0 || size == 0 || type == 0 || resources.size() == 0)
        Usage();

    DiskUsage du(depth, size, type);
    QStringList list = du.process(resources);
    QTextStream cout(stdout);
    for (int i = 0; i < list.size(); i += 2)
    {
        cout << list.at(i) << "\t" << list.at(i+1) << endl;
    }

    return 0;
}
