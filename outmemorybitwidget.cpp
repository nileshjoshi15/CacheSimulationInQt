#include "outmemorybitwidget.h"
#include<QHBoxLayout>
#include<QLabel>
#include "commonuiproperties.h"
#include "commonutil.h"
#include<QDebug>

OutMemoryBitWidget::OutMemoryBitWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *sectionBox = new QHBoxLayout;
    sectionBox->addWidget(SetUpWidget());
    setLayout(sectionBox);
}


QGroupBox*  OutMemoryBitWidget::SetUpWidget(){
    QGroupBox *groupBox = new QGroupBox(tr("Output Panel"));
    /* Main layout for this groupbox */
    QHBoxLayout *hMainRightBottomBox = new QHBoxLayout;
    /*Left Bottom Labels*/
    QVBoxLayout *vRightBottomBox1 = new QVBoxLayout;
    LabelGroupUI(vRightBottomBox1);

    /*Top Right UI control */
    QVBoxLayout *vBottomRightDisplayBox = new QVBoxLayout;
    GroupLCDUI(vBottomRightDisplayBox);

    /*Add items to layout*/
    hMainRightBottomBox->addLayout(vRightBottomBox1);
    hMainRightBottomBox->addLayout(vBottomRightDisplayBox);
    groupBox->setLayout(hMainRightBottomBox);
    groupBox->setFixedSize(350,150);
    return groupBox;
}

void OutMemoryBitWidget::load_change_values(int main_memory_new,int set_new,QString byte_per_block_new,int blocks_per_set_new){
    ref_lcd->display(QString::number(CommonUtil::byteToBit(main_memory_new)));
    offset_lcd->display(QString::number(CommonUtil::byteToBit(byte_per_block_new.toInt())));
    index_lcd->display(CommonUtil::byteToBit(set_new));

    int tag=ref_lcd->value()-offset_lcd->value()-index_lcd->value();
    tag_lcd->display(tag);
}

void OutMemoryBitWidget::GroupLCDUI(QVBoxLayout *vBottomRightDisplayBox)
{
    ref_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(ref_lcd,1.5);

    offset_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(offset_lcd,1.5);

    index_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(index_lcd,1.5);

    tag_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(tag_lcd,1.5);

    vBottomRightDisplayBox->addWidget(ref_lcd);
    vBottomRightDisplayBox->addWidget(offset_lcd);
    vBottomRightDisplayBox->addWidget(index_lcd);
    vBottomRightDisplayBox->addWidget(tag_lcd);
}

void OutMemoryBitWidget::LabelGroupUI(QVBoxLayout *vRightBottomBox1)
{
    QLabel *ref_lbl = new QLabel(tr("Reference word Size : "));
    ref_lbl->setAlignment(Qt::AlignRight);
    vRightBottomBox1->addWidget(ref_lbl);

    QLabel *offset_lbl = new QLabel(tr("Offset field size : "));
    offset_lbl->setAlignment(Qt::AlignRight);
    vRightBottomBox1->addWidget(offset_lbl);

    QLabel *index_lbl = new QLabel(tr("Index Field Size : "));
    index_lbl->setAlignment(Qt::AlignRight);
    vRightBottomBox1->addWidget(index_lbl);

    QLabel *tag_lbl = new QLabel(tr("Tag field size : "));
    tag_lbl->setAlignment(Qt::AlignRight);
    vRightBottomBox1->addWidget(tag_lbl);
}
