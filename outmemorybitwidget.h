#ifndef OUTMEMORYBITWIDGET_H
#define OUTMEMORYBITWIDGET_H

#include <QWidget>
#include<QGroupBox>
#include<QLCDNumber>
#include<QVBoxLayout>

class OutMemoryBitWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutMemoryBitWidget(QWidget *parent = 0);

private:
    QLCDNumber *ref_lcd;
    QLCDNumber *offset_lcd;
    QLCDNumber *index_lcd;
    QLCDNumber *tag_lcd;
    QGroupBox* SetUpWidget();
    void GroupLCDUI(QVBoxLayout *vBottomRightDisplayBox);

    void LabelGroupUI(QVBoxLayout *vRightBottomBox1);

signals:

public slots:
    void load_change_values(int main_memory_new,int set_new,QString byte_per_block_new,int blocks_per_set_new);
};

#endif // OUTMEMORYBITWIDGET_H
