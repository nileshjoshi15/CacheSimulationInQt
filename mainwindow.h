#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>
#include<QTextEdit>
#include<QGroupBox>
#include<QProgressDialog>
#include<QDockWidget>
#include<QLCDNumber>
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include "simmulationmodel.h"
#include "policywidget.h"
#include "memorywidget.h"
#include "outparamwidget.h"
#include "outmemorybitwidget.h"

class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    void createActions();
    void createMenus();
    void createCacheDockWidget();
    void setupUiItems(QWidget *widget);
    void CollectUiInputs();
    QString  formatErrorMsg(QList<QString> errorMessages);
    QProgressDialog *customProgessDig(QString titlemsg);
    void init_val();
    void ActionButtonGroups(QHBoxLayout *bhLayout);

    /*Menu items and methods */
    QMenu *fileMenu;
    QAction *openAction;
    QAction *closeAction;
    QMenu *helpMenu;
    QAction *helpAction;

    QDockWidget *dock_cache;
    /*UI items for simulation*/
    QLabel *infoLabel;

    /*Simulation Parameter Placeholder*/
    InputViewModel paramModel;

    PolicyWidget *policy_widget;
    MemoryWidget *memory_widget;
    OutParamWidget *out_param_widget;
    OutMemoryBitWidget *out_mem_bit_widget;


signals:
    void sim_value_changed(int main_memory_new,int set_new,QString byte_per_block_new,int blocks_per_set_new);

private slots:
    void open();
    void closeApp();
    void help();
    void on_Submit_clickMain();
    void UpdatePolicyType(int pol_index,bool ins,bool data);
    void UpdateMemSimParam(int main_memory_new,int set_new,QString byte_per_block_new,int blocks_per_set_new);

};

#endif // MAINWINDOW_H
