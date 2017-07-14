#ifndef ERRORMSGCODE_H
#define ERRORMSGCODE_H
#include<QApplication>
#include<QList>

struct ErrorMsgCode{
    bool IsError;
    QList<QString> errorMessage;
};

#endif // ERRORMSGCODE_H
