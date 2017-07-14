#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include<QGroupBox>

#include<QLineEdit>
#include<QScrollBar>
#include<QSpinBox>
#include<QSlider>
#include<QVBoxLayout>

class MemoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MemoryWidget(QWidget *parent = 0);

private:
    QGroupBox* SetUpWidget();

    QScrollBar *main_memory;
    QSpinBox *noSetSpin;
    QSlider *blockPerSetSlider;
    QLineEdit *bytePerBlocklnEt;

    void GroupLCDItems(QVBoxLayout *vRightBottomDisplayBox);

    QVBoxLayout * UiControlGroup();

    void UIControlGroup(QVBoxLayout *vRightBottomBox);

    void GroupLabelItems(QVBoxLayout *vLeftTopBox11);

signals:
    void sim_param_changed(int main_memory_new,int set_new,QString byte_per_block_new,int blocks_per_set_new);

private slots:
    void main_memory_changed(int value);
    void set_changed(int value);
    void byte_per_block_changed(QString value);
    void blocks_per_set_changed(int value);
};

#endif // MEMORYWIDGET_H
