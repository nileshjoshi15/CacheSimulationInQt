#ifndef POLICYWIDGET_H
#define POLICYWIDGET_H

#include <QWidget>
#include<QComboBox>
#include<QRadioButton>
#include<QGroupBox>
#include<QHBoxLayout>
#include "simmulationmodel.h"

class PolicyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PolicyWidget(QWidget *parent = 0);


private:
    /*Simulation Parameter Placeholder*/
    InputViewModel paramModel;
    QGroupBox* SetUpWidget();
    QComboBox *replaceCombo;
    QRadioButton *cacheInsRadio;
    QRadioButton *cacheDataRadio;


    void GroupLabelUI(QVBoxLayout *vRight1TopBox);

    void GroupUIItems(QVBoxLayout *vRight2TopBox);

signals:
    void policy_rep_changed(int pol,bool ins,bool data);

private slots:
    void pol_val_changed(int val);
    void ins_checked(bool val);
    void data_checked(bool val);
};

#endif // POLICYWIDGET_H
