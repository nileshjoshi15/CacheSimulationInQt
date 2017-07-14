#ifndef OUTPARAMWIDGET_H
#define OUTPARAMWIDGET_H

#include <QWidget>
#include<QGroupBox>
#include<QLCDNumber>
#include<QHBoxLayout>
#include<simmulationmodel.h>

class OutParamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutParamWidget(QWidget *parent = 0);
    void DisplayOutLCD(OutputViewModel out);

private:
    QGroupBox* SetUpWidget();
    QLCDNumber *no_mem_access_lcd;
    QLCDNumber *hit_ratio_lcd;
    QLCDNumber *comp_miss_lcd;
    QLCDNumber *miss_ratio_lcd;
    void LabelUIGroup(QVBoxLayout *vLeftBottomBox1);
    void LCDGroupUI(QVBoxLayout *vBottomLeftDisplayBox);

signals:

public slots:
};

#endif // OUTPARAMWIDGET_H
