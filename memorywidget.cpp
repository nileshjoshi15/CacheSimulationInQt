#include "memorywidget.h"
#include<QVBoxLayout>
#include<QLabel>
#include<QDebug>
#include "commonuiproperties.h"

MemoryWidget::MemoryWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *sectionBox = new QHBoxLayout;
    sectionBox->addWidget(SetUpWidget());
    setLayout(sectionBox);
}

QGroupBox*  MemoryWidget::SetUpWidget(){

    QGroupBox *groupBox = new QGroupBox(tr("Set Associative Parameters"));
    QHBoxLayout *hMainTopBox = new QHBoxLayout;

    /*Left Bottom Labels*/
    QVBoxLayout *vLeftTopBox11 = new QVBoxLayout;
    GroupLabelItems(vLeftTopBox11);


    /*Bottom right UI control */
    QVBoxLayout *vRightBottomBox = new QVBoxLayout;
    UIControlGroup(vRightBottomBox);

    /*Top Right UI control */
    QVBoxLayout *vRightBottomDisplayBox = new QVBoxLayout;
    GroupLCDItems(vRightBottomDisplayBox);

    /*Notify others */
    connect(main_memory,SIGNAL(valueChanged(int)),this,SLOT(main_memory_changed(int)));
    connect(noSetSpin,SIGNAL(valueChanged(int)),this,SLOT(set_changed(int)));
    connect(bytePerBlocklnEt,SIGNAL(textChanged(QString)),this,SLOT(byte_per_block_changed(QString)));
    connect(blockPerSetSlider,SIGNAL(valueChanged(int)),this,SLOT(blocks_per_set_changed(int)));

    /*Add items to layout*/
    hMainTopBox->addLayout(vLeftTopBox11);
    hMainTopBox->addLayout(vRightBottomBox);
    hMainTopBox->addLayout(vRightBottomDisplayBox);

    groupBox->setLayout(hMainTopBox);
    groupBox->setFixedSize(450,150);
    return groupBox;
}

void MemoryWidget::main_memory_changed(int value){
    emit sim_param_changed(value,noSetSpin->value(),bytePerBlocklnEt->text(),blockPerSetSlider->value());
}

void MemoryWidget::set_changed(int value){
    emit sim_param_changed(main_memory->value(),value,bytePerBlocklnEt->text(),blockPerSetSlider->value());
}

void MemoryWidget::byte_per_block_changed(QString value){
    emit sim_param_changed(main_memory->value(),noSetSpin->value(),value,blockPerSetSlider->value());
}

void MemoryWidget::blocks_per_set_changed(int value){
    emit sim_param_changed(main_memory->value(),noSetSpin->value(),bytePerBlocklnEt->text(),value);
}


/*UI Control Group*/
void MemoryWidget::UIControlGroup(QVBoxLayout *vRightBottomBox)
{
    main_memory=new QScrollBar(Qt::Horizontal);
    main_memory->setRange(256,1024*1024*255);
    main_memory->setValue(256);
    vRightBottomBox->addWidget(main_memory);

    bytePerBlocklnEt=new QLineEdit;
    vRightBottomBox->addWidget(bytePerBlocklnEt);

    noSetSpin= new QSpinBox;
    noSetSpin->setRange(0,16);
    noSetSpin->setValue(0);

    blockPerSetSlider = new QSlider(Qt::Horizontal);
    blockPerSetSlider->setRange(0,16);
    blockPerSetSlider->setValue(0);
    vRightBottomBox->addWidget(noSetSpin);
    vRightBottomBox->addWidget(blockPerSetSlider);
}

/*Grouping Label Items*/
void MemoryWidget::GroupLabelItems(QVBoxLayout *vLeftTopBox11)
{
    QLabel *main_memorylbl = new QLabel(tr("Main Memory Size(M) : "));
    main_memorylbl->setAlignment(Qt::AlignRight);
    vLeftTopBox11->addWidget(main_memorylbl);

    QLabel *bytePerBlockLbl = new QLabel(tr("Byte Per Block(K) : "));
    bytePerBlockLbl->setAlignment(Qt::AlignRight);
    vLeftTopBox11->addWidget(bytePerBlockLbl);
    QLabel *numSetLbl = new QLabel(tr("Number of Sets (N) : "));
    numSetLbl->setAlignment(Qt::AlignRight);
    vLeftTopBox11->addWidget(numSetLbl);
    QLabel *blockPerSetLbl = new QLabel(tr("Number of Ways(L) : "));
    blockPerSetLbl->setAlignment(Qt::AlignRight);
    vLeftTopBox11->addWidget(blockPerSetLbl);
}

/*LCD item group */
void MemoryWidget::GroupLCDItems(QVBoxLayout *vRightBottomDisplayBox)
{
    QLCDNumber *main_memory_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(main_memory_lcd,1);
    main_memory_lcd->display(256);

    QLCDNumber *block_size_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(block_size_lcd,1);

    QLCDNumber *no_set_spin_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(no_set_spin_lcd,1);

    QLCDNumber *block_per_set_lcd =new QLCDNumber;
    CommonUiProperties::ChangeLcdProperties(block_per_set_lcd,1);

    vRightBottomDisplayBox->addWidget(main_memory_lcd);
    vRightBottomDisplayBox->addWidget(block_size_lcd);
    vRightBottomDisplayBox->addWidget(no_set_spin_lcd);
    vRightBottomDisplayBox->addWidget(block_per_set_lcd);

    /*Signal and slots for LCD Display*/
    connect(main_memory,SIGNAL(valueChanged(int)),main_memory_lcd,SLOT(display(int)));
    connect(bytePerBlocklnEt,SIGNAL(textChanged(QString)),block_size_lcd,SLOT(display(QString)));
    connect(noSetSpin,SIGNAL(valueChanged(int)),no_set_spin_lcd,SLOT(display(int)));
    connect(blockPerSetSlider,SIGNAL(valueChanged(int)),block_per_set_lcd,SLOT(display(int)));


}
