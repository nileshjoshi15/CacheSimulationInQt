#ifndef FILEUTIL_H
#define FILEUTIL_H
#include<QList>
#include<QProgressDialog>

class FileUtil
{
public:
    FileUtil();
    static QList<unsigned long> ReadTraceFileInHEX(QString file);
    static void WriteToFile(QString file,QString content);
    static QList<QString> ProcessTraceFile(QString file);

};

#endif // FILEUTIL_H
