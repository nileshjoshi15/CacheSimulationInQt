#include "policywidget.h"

#include<QHBoxLayout>
#include<QLabel>
#include<QDebug>

PolicyWidget::PolicyWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *sectionBox = new QHBoxLayout;
    sectionBox->addWidget(SetUpWidget());
    connect(replaceCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(pol_val_changed(int)));
    connect(cacheInsRadio,SIGNAL(clicked(bool)),this,SLOT(ins_checked(bool)));
    connect(cacheDataRadio,SIGNAL(clicked(bool)),this,SLOT(data_checked(bool)));
    setLayout(sectionBox);
}

QGroupBox*  PolicyWidget::SetUpWidget(){
    QGroupBox *groupBox = new QGroupBox(tr("Simulation type and Replacement policies"));
    QHBoxLayout *hMainLeftBox = new QHBoxLayout;
    QVBoxLayout *vRight1TopBox = new QVBoxLayout;
    GroupLabelUI(vRight1TopBox);
    QVBoxLayout *vRight2TopBox = new QVBoxLayout;
    GroupUIItems(vRight2TopBox);
    hMainLeftBox->addLayout(vRight1TopBox);
    hMainLeftBox->addLayout(vRight2TopBox);
    groupBox->setLayout(hMainLeftBox);
    groupBox->setFixedSize(440,100);
    return groupBox;
}


void PolicyWidget::pol_val_changed(int value){
    emit policy_rep_changed(value,cacheInsRadio->isChecked(),cacheDataRadio->isChecked());
}


void PolicyWidget::data_checked(bool value){
    emit policy_rep_changed(replaceCombo->itemData(replaceCombo->currentIndex()).toInt(),cacheInsRadio->isChecked(),value);
}


void PolicyWidget::ins_checked(bool value){
    emit policy_rep_changed(replaceCombo->itemData(replaceCombo->currentIndex()).toInt(),value,cacheDataRadio->isChecked());
}


void PolicyWidget::GroupUIItems(QVBoxLayout *vRight2TopBox)
{
    replaceCombo =new QComboBox;
    replaceCombo->addItem("Select Item",QVariant::fromValue(-1));
    replaceCombo->addItem("LRU Alg",QVariant::fromValue(1));
    replaceCombo->addItem("LFU Alg",QVariant::fromValue(2));
    replaceCombo->addItem("Random Alg",QVariant::fromValue(3));
    vRight2TopBox->addWidget(replaceCombo);

    QHBoxLayout *layoutRadio = new QHBoxLayout;
    cacheInsRadio=new QRadioButton(tr("Instruction"));
    cacheInsRadio->setChecked(true);
    cacheDataRadio=new QRadioButton(tr("Data"));
    layoutRadio->addWidget(cacheDataRadio);\
    layoutRadio->addWidget(cacheInsRadio);
    vRight2TopBox->addLayout(layoutRadio);
}

void PolicyWidget::GroupLabelUI(QVBoxLayout *vRight1TopBox)
{
    QLabel *replacePolLbl = new QLabel(tr("Select Replacement Policy : "));
    replacePolLbl->setAlignment(Qt::AlignRight);

    vRight1TopBox->addWidget(replacePolLbl);
    QLabel *cacheTypeLbl = new QLabel(tr("Select Cache Type : "));
    cacheTypeLbl->setAlignment(Qt::AlignRight);
    vRight1TopBox->addWidget(cacheTypeLbl);
}





