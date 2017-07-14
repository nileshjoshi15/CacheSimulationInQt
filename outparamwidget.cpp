#include "outparamwidget.h"
#include<QHBoxLayout>
#include<QLabel>
#include<QDebug>
#include "commonuiproperties.h"
#include "simmulationmodel.h"

OutParamWidget::OutParamWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *sectionBox = new QHBoxLayout;
    sectionBox->addWidget(SetUpWidget());
    setLayout(sectionBox);
}

void OutParamWidget::DisplayOutLCD(OutputViewModel out){
    double miss=(out.no_hit*100)/(1.0*out.mem_access);
    no_mem_access_lcd->display(QString::number(out.mem_access));
    hit_ratio_lcd->display(QString::number((out.no_hit*100)/(1.0*out.mem_access)));
    miss_ratio_lcd->display(QString::number((out.no_miss*100)/(1.0*out.mem_access)));
    comp_miss_lcd->display(QString::number((out.compusory_miss*100)/(1.0*out.mem_access)));
}


void OutParamWidget::LCDGroupUI(QVBoxLayout *vBottomLeftDisplayBox)
{
    no_mem_access_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(no_mem_access_lcd,1.5);

    hit_ratio_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(hit_ratio_lcd,1.5);

    comp_miss_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(comp_miss_lcd,1.5);

    miss_ratio_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(miss_ratio_lcd,1.5);
    vBottomLeftDisplayBox->addWidget(no_mem_access_lcd);
    vBottomLeftDisplayBox->addWidget(hit_ratio_lcd);
    vBottomLeftDisplayBox->addWidget(miss_ratio_lcd);
    vBottomLeftDisplayBox->addWidget(comp_miss_lcd);
}

QGroupBox*  OutParamWidget::SetUpWidget(){
    QGroupBox *groupBox = new QGroupBox(tr("Output Panel"));
    /* Main layout for this groupbox */
    QHBoxLayout *hMainLeftBottomBox = new QHBoxLayout;
    /*Left Bottom Labels*/
    QVBoxLayout *vLeftBottomBox1 = new QVBoxLayout;

    LabelUIGroup(vLeftBottomBox1);
    /*Top Right UI control */
    QVBoxLayout *vBottomLeftDisplayBox = new QVBoxLayout;
    LCDGroupUI(vBottomLeftDisplayBox);

    /*Add items to layout*/
    hMainLeftBottomBox->addLayout(vLeftBottomBox1);
    hMainLeftBottomBox->addLayout(vBottomLeftDisplayBox);
    groupBox->setLayout(hMainLeftBottomBox);
    groupBox->setFixedSize(350,150);
    return groupBox;
}



void OutParamWidget::LabelUIGroup(QVBoxLayout *vLeftBottomBox1)
{
    QLabel *no_mem_accesslbl = new QLabel(tr("No. of memory Access : "));
    no_mem_accesslbl->setAlignment(Qt::AlignRight);
    vLeftBottomBox1->addWidget(no_mem_accesslbl);

    QLabel *hit_ratioLbl = new QLabel(tr("Hit Ratio : "));
    hit_ratioLbl->setAlignment(Qt::AlignRight);
    vLeftBottomBox1->addWidget(hit_ratioLbl);

    QLabel *miss_ratioLbl = new QLabel(tr("Miss Ratio : "));
    miss_ratioLbl->setAlignment(Qt::AlignRight);
    vLeftBottomBox1->addWidget(miss_ratioLbl);

    QLabel *comp_missLbl = new QLabel(tr("Compulsory Miss Ratio : "));
    comp_missLbl->setAlignment(Qt::AlignRight);
    vLeftBottomBox1->addWidget(comp_missLbl);
}
