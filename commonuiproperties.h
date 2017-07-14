#ifndef COMMONUIPROPERTIES_H
#define COMMONUIPROPERTIES_H
#include<QMainWindow>
#include<QLCDNumber>
#include<QLabel>
#include<QPushButton>
#include<QProgressDialog>
#include<QProgressBar>
#include<QList>

class CommonUiProperties
{
public:
    CommonUiProperties();
    static void ChangeLcdProperties(QLCDNumber *inQlcd,float factor);
    static void ChangeLabelProperties(QLabel *inQlbl,QColor color);
    static void DisplayMsg(QString msg);
    static void PushProperties(QPushButton *msg);
    static void StyleMessageBox(QWidget* window);
    static QProgressDialog* customProgessDig(QString titlemsg,QMainWindow *window);
    static QString formatErrorMsg(QList<QString> errorMessages);

};

#endif // COMMONUIPROPERTIES_H
