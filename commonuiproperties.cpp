#include "commonuiproperties.h"
#include<QMessageBox>
#include<QStringBuilder>

CommonUiProperties::CommonUiProperties()
{

}

void CommonUiProperties::ChangeLabelProperties(QLabel *inQlbl, QColor color){
    inQlbl->setAutoFillBackground(true);
    QPalette myPal = inQlbl->palette();
    myPal.setColor(QPalette::Normal, QPalette::WindowText,color);
    inQlbl->setPalette(myPal);
}


void CommonUiProperties::ChangeLcdProperties(QLCDNumber *inQlcd,float factor){
    inQlcd->setAutoFillBackground(true);
    inQlcd->setFixedWidth(120);
    inQlcd->setStyleSheet("* {background-color:grey;}");
    inQlcd->setDigitCount(12);
    QPalette myPal = inQlcd->palette();
    inQlcd->setPalette(myPal);
}

void CommonUiProperties::DisplayMsg(QString msg){
     QMessageBox alertBox;
     alertBox.setInformativeText(msg);
     alertBox.setStandardButtons(QMessageBox::Ok);
     alertBox.exec();
}

void CommonUiProperties::PushProperties(QPushButton *msg){
    msg->setMaximumWidth(80);
}

void CommonUiProperties::StyleMessageBox(QWidget *widget){
    widget->setStyleSheet("QMessageBox {border-radius: 0px; }");
}

QString CommonUiProperties:: formatErrorMsg(QList<QString> errorMessages){
    QString formateed_msg ="<font color='red'><b>Please correct following error(s)</b><br>";
    foreach (QString errormsg, errorMessages) {
        formateed_msg=formateed_msg%"*** "%errormsg%"<br>";
    }
    formateed_msg=formateed_msg%"</font>";
    return formateed_msg;
}


QProgressDialog *CommonUiProperties::customProgessDig(QString titlemsg,QMainWindow *window){
    QProgressDialog *progress=new QProgressDialog(titlemsg,"Cancel",0,INT_MAX,window);
    QProgressBar *bar = new QProgressBar(progress);
    bar->setRange(0,0);
    bar->setValue(0);
    progress->setBar(bar);
    progress->setModal(true);
    progress->setCancelButton(NULL);
    return progress;
}


