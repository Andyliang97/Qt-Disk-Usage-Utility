#include <QtTest/QtTest>
#include <diskusage.h>

class TestDiskUsage : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    
    void test01();
    void test02();
    void test03();
    void test04();
    void test05();
    void test06();
    void test07();
    void test08();
    void test09();
    void test10();
    void test11();
};

void TestDiskUsage::initTestCase()
{
	QDir("basis").removeRecursively();
	QVERIFY(QDir().mkpath("basis/A/E"));
	QVERIFY(QDir().mkpath("basis/B/A"));
	QVERIFY(QDir().mkpath("basis/B/B"));

	QFile file1k("basis/1k");
	file1k.open(QIODevice::WriteOnly);
	QVERIFY(file1k.resize(1024));
	file1k.close();

	QFile fileempty("basis/A/empty");
	fileempty.open(QIODevice::WriteOnly);
	fileempty.close();

	QFile file2k("basis/A/2k");
	file2k.open(QIODevice::WriteOnly);
	QVERIFY(file2k.resize(1024 * 2));
	file2k.close();

	QFile file35k("basis/B/A/3.5k");
	file35k.open(QIODevice::WriteOnly);
	QVERIFY(file35k.resize(1024 * 3.5));
	file35k.close();
	
	QVERIFY(QFile::copy("basis/1k", "basis/A/1k"));
	QVERIFY(QFile::copy("basis/1k", "basis/B/1k"));

	QVERIFY(QFile::copy("basis/A/2k", "basis/B/2k"));
	QVERIFY(QFile::copy("basis/A/2k", "basis/B/A/2k"));
	QVERIFY(QFile::copy("basis/A/2k", "basis/B/B/2k"));

	QVERIFY(QFile::copy("basis/B/A/3.5k", "basis/B/B/3.5k"));

	QVERIFY(QFile::link("../B", "basis/B/backlink"));
}

void TestDiskUsage::test01()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_BYTE;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_DIR) | (1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
    QStringList result = QStringList() << "1024 B" << "basis/1k" << "11264 B" << "basis/A/" << "1024 B" << "basis/A/1k" << "2048 B" << "basis/A/2k" << "4096 B" << "basis/A/E" << "0 B" << "basis/A/empty" << "30720 B" << "basis/B/" << "1024 B" << "basis/B/1k" << "2048 B" << "basis/B/2k" << "9728 B" << "basis/B/A" << "2048 B" << "basis/B/A/2k" << "3584 B" << "basis/B/A/3.5k" << "9728 B" << "basis/B/B" << "2048 B" << "basis/B/B/2k" << "3584 B" << "basis/B/B/3.5k" << "4096 B" << "basis/B/backlink";
    QCOMPARE(out, result);
}

void TestDiskUsage::test02()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = 0; 
    UnitSize size = SIZE_BYTE;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_DIR) | (1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
    QStringList result = QStringList() << "1024 B" << "basis/1k" << "11264 B" << "basis/A/" << "30720 B" << "basis/B/";
    QCOMPARE(out, result);
}

void TestDiskUsage::test03()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = 1; 
    UnitSize size = SIZE_BYTE;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_DIR) | (1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
    QStringList result = QStringList() << "1024 B" << "basis/1k" << "11264 B" << "basis/A/" << "1024 B" << "basis/A/1k" << "2048 B" << "basis/A/2k" << "4096 B" << "basis/A/E" << "0 B" << "basis/A/empty" << "30720 B" << "basis/B/" << "1024 B" << "basis/B/1k" << "2048 B" << "basis/B/2k" << "9728 B" << "basis/B/A" << "9728 B" << "basis/B/B" << "4096 B" << "basis/B/backlink";
    QCOMPARE(out, result);
}

void TestDiskUsage::test04()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = 2; 
    UnitSize size = SIZE_BYTE;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_DIR) | (1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
	QStringList result = QStringList() << "1024 B" << "basis/1k" << "11264 B" << "basis/A/" << "1024 B" << "basis/A/1k" << "2048 B" << "basis/A/2k" << "4096 B" << "basis/A/E" << "0 B" << "basis/A/empty" << "30720 B" << "basis/B/" << "1024 B" << "basis/B/1k" << "2048 B" << "basis/B/2k" << "9728 B" << "basis/B/A" << "2048 B" << "basis/B/A/2k" << "3584 B" << "basis/B/A/3.5k" << "9728 B" << "basis/B/B" << "2048 B" << "basis/B/B/2k" << "3584 B" << "basis/B/B/3.5k" << "4096 B" << "basis/B/backlink";
    QCOMPARE(out, result);
}

void TestDiskUsage::test05()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_KB;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_DIR) | (1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);

	QStringList result = QStringList() << "1 kB" << "basis/1k" << "11 kB" << "basis/A/" << "1 kB" << "basis/A/1k" << "2 kB" << "basis/A/2k" << "4 kB" << "basis/A/E" << "0 kB" << "basis/A/empty" << "30 kB" << "basis/B/" << "1 kB" << "basis/B/1k" << "2 kB" << "basis/B/2k" << "10 kB" << "basis/B/A" << "2 kB" << "basis/B/A/2k" << "4 kB" << "basis/B/A/3.5k" << "10 kB" << "basis/B/B" << "2 kB" << "basis/B/B/2k" << "4 kB" << "basis/B/B/3.5k" << "4 kB" << "basis/B/backlink";
    QCOMPARE(out, result);
}

void TestDiskUsage::test06()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_MB;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_DIR) | (1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
	QStringList result = QStringList() << "1 MB" << "basis/1k" << "1 MB" << "basis/A/" << "1 MB" << "basis/A/1k" << "1 MB" << "basis/A/2k" << "1 MB" << "basis/A/E" << "0 MB" << "basis/A/empty" << "1 MB" << "basis/B/" << "1 MB" << "basis/B/1k" << "1 MB" << "basis/B/2k" << "1 MB" << "basis/B/A" << "1 MB" << "basis/B/A/2k" << "1 MB" << "basis/B/A/3.5k" << "1 MB" << "basis/B/B" << "1 MB" << "basis/B/B/2k" << "1 MB" << "basis/B/B/3.5k" << "1 MB" << "basis/B/backlink";
    QCOMPARE(out, result);
}

void TestDiskUsage::test07()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_BYTE;
    ResourceType type = (1 << TYPE_FILE);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
	QStringList result = QStringList() << "1024 B" << "basis/1k" << "1024 B" << "basis/A/1k" << "2048 B" << "basis/A/2k" << "0 B" << "basis/A/empty" << "1024 B" << "basis/B/1k" << "2048 B" << "basis/B/2k" << "2048 B" << "basis/B/A/2k" << "3584 B" << "basis/B/A/3.5k" << "2048 B" << "basis/B/B/2k" << "3584 B" << "basis/B/B/3.5k";
    QCOMPARE(out, result);
}

void TestDiskUsage::test08()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_BYTE;
    ResourceType type =(1 << TYPE_DIR);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
	QStringList result = QStringList() << "11264 B" << "basis/A/" << "4096 B" << "basis/A/E" << "30720 B" << "basis/B/" << "9728 B" << "basis/B/A" << "9728 B" << "basis/B/B";
    QCOMPARE(out, result);
}

void TestDiskUsage::test09()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_BYTE;
    ResourceType type =(1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
	QStringList result = QStringList() << "4096 B" << "basis/B/backlink";
    QCOMPARE(out, result);
}

void TestDiskUsage::test10()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_BYTE;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_SYM);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
	QStringList result = QStringList() << "1024 B" << "basis/1k" << "1024 B" << "basis/A/1k" << "2048 B" << "basis/A/2k" << "0 B" << "basis/A/empty" << "1024 B" << "basis/B/1k" << "2048 B" << "basis/B/2k" << "2048 B" << "basis/B/A/2k" << "3584 B" << "basis/B/A/3.5k" << "2048 B" << "basis/B/B/2k" << "3584 B" << "basis/B/B/3.5k" << "4096 B" << "basis/B/backlink";
    QCOMPARE(out, result);
}

void TestDiskUsage::test11()
{
    QStringList resources = QStringList() << "basis/B/" << "basis/1k" << "basis/A/";
    qint64 depth = MAX_DEPTH; 
    UnitSize size = SIZE_BYTE;
    ResourceType type = (1 << TYPE_FILE) | (1 << TYPE_DIR);

    DiskUsage usage(depth, size, type);
    QStringList out = usage.process(resources);
    
	QStringList result = QStringList() << "1024 B" << "basis/1k" << "11264 B" << "basis/A/" << "1024 B" << "basis/A/1k" << "2048 B" << "basis/A/2k" << "4096 B" << "basis/A/E" << "0 B" << "basis/A/empty" << "30720 B" << "basis/B/" << "1024 B" << "basis/B/1k" << "2048 B" << "basis/B/2k" << "9728 B" << "basis/B/A" << "2048 B" << "basis/B/A/2k" << "3584 B" << "basis/B/A/3.5k" << "9728 B" << "basis/B/B" << "2048 B" << "basis/B/B/2k" << "3584 B" << "basis/B/B/3.5k";
    QCOMPARE(out, result);
}

QTEST_MAIN(TestDiskUsage)
#include "testdiskusage.moc"
