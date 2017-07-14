#include "fileutil.h"
#include<QStringBuilder>
#include<QDebug>
#include<QFile>

FileUtil::FileUtil()
{

}

QList<unsigned long> FileUtil::ReadTraceFileInHEX(QString file){
   QFile fileNameIn(file);
   QList<unsigned long> memAddresses;
   try{
       if (!fileNameIn.open(QIODevice::ReadOnly)){
            return memAddresses;
       }
       QTextStream memStream(&fileNameIn);
       QString memAddress = memStream.readLine();
       while (!memAddress.isNull()) {
           bool IsSucess=false;
           unsigned long memAddrInt=memAddress.toUInt(&IsSucess,16);
           if(IsSucess){
                memAddresses.append(memAddrInt);
           }else{
               qDebug()<<"Error on converting address";
           }
           memAddress = memStream.readLine();
       }
       return memAddresses;
   }
   catch(std::exception &e){
       qDebug()<<"Error occured";
   }
}



QList<QString> FileUtil::ProcessTraceFile(QString file){
   QFile fileNameIn(file);
   QList<QString> memAddresses;
   try{
       if (!fileNameIn.open(QIODevice::ReadOnly)){
            return memAddresses;
       }
       QTextStream memStream(&fileNameIn);
       QString memAddress = memStream.readLine();
       while (!memAddress.isNull()) {
           if(memAddress!=""){
               memAddress="0x"%memAddress;
               memAddresses.append(memAddress);
               qDebug()<<memAddress;
           }
           memAddress = memStream.readLine();

       }
       return memAddresses;
   }
   catch(std::exception &e){
       qDebug()<<"Error occured";
   }
}

void FileUtil::WriteToFile(QString dir,QString content){
    QFile outfile(dir);
    if(!outfile.open(QIODevice::ReadWrite)){
        qDebug()<<"error ";
    }
    QTextStream out(&outfile);
    out <<content << endl;
    qDebug()<<"testing save ";
}
