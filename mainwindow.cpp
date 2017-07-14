#include<QTextEdit>
#include<QMenuBar>
#include<QDockWidget>
#include<QPushButton>
#include<QProgressBar>
#include<QMessageBox>
#include<QStringBuilder>
#include<QFileDialog>
#include<QDebug>
#include "mainwindow.h"
#include "commonuiproperties.h"
#include "errormsgcode.h"
#include "validateuival.h"
#include "fileutil.h"
#include "commonutil.h"
#include "setassociativememsim.h"
#include<QMouseEvent>

MainWindow::MainWindow()
{

    init_val();
    createActions();
    createMenus();
    createCacheDockWidget();

}

/*Start simulation button click event*/
void MainWindow ::  on_Submit_clickMain(){
    QMessageBox *msgBox=new QMessageBox;

    /*validate all user input and file before continuing*/
    ErrorMsgCode errorMsg=ValidateUiVal::ValidateUI(paramModel,0);
    if(errorMsg.IsError){
        msgBox->warning(this,"Warning",CommonUiProperties::formatErrorMsg(errorMsg.errorMessage));
        return;
    }
    setAssociativeMemSim set(paramModel);
    OutputViewModel result=set.InspectMemAddr();
    out_param_widget->DisplayOutLCD(result);

}


/*Create action and related Signal*/
void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    closeAction = new QAction(tr("&Close..."), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeApp()));

    helpAction = new QAction(tr("&Help"),this);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));
}


/*Create file menu and attach actions */
void MainWindow::createMenus()
{
    /*File menu and items under*/
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);

    /*About menu and items under*/
    helpMenu=menuBar()->addMenu((tr("&About")));
    helpMenu->addAction(helpAction);
}




/*Open action implementation*/
void MainWindow::open()
{
    paramModel.file_name= QFileDialog::getOpenFileName(this);

    if(paramModel.file_name!=NULL){
        QStringList names=paramModel.file_name.split('/');

        QStringList ext=names.at(names.size()-1).split('.');
        QString file_extension=ext.at(ext.size()-1);

        QStringList unsupported_ext;
        unsupported_ext<<"doc"<<"docx"<<"pdf"<<"o";

        if(unsupported_ext.indexOf(file_extension)!=-1){
            QMessageBox::warning(this, tr("Warning"),
                     tr("<font color='red'>You may feel unexpected behaviour with this extension type.</font>"));
        }

        infoLabel->setText(names.at(names.size()-1));
         qDebug()<<"Etst";
        CommonUiProperties::ChangeLabelProperties(infoLabel,Qt::green);
        return;
    }
    infoLabel->setText(tr("<b>**File is not selected**</b>"));
    CommonUiProperties::ChangeLabelProperties(infoLabel,Qt::red);
}


/*Close App code Implementation*/
void MainWindow::closeApp(){
     QMessageBox *msgBox=new QMessageBox;
     QMessageBox::StandardButton decision;
    /*Confirmation message before close*/
    decision=  msgBox->question(this,"You Decision",
                                    "Are you sure you want to quit",
                                    QMessageBox::Yes|QMessageBox::No);

    /*Confirm user wants to exit or not?*/
    if(decision==QMessageBox::Yes){
        this->close();
        return;
    }
}


/* Help slot implementation */
void MainWindow::help()
{
   QMessageBox::about(this, tr("Cache Simulation Help"),
            tr("1. Please use \"Open Graphics Widget\" button to switch between \"Cache dock widget\" and \"Graphics dock widget\"<br><br>"
               "2. After prepending a 0x into the address, content will be displayed on the text editor "
               "which can be saved into same file or different file. Please use "
               "\"Save\" option under file menu to save changes into same file Or use \"Save as\" option "
               "if you want to save in different file name.<br>"));
}


/*Cache dock widget UI item load code*/
void MainWindow::createCacheDockWidget(){

    QWidget *widget = new QWidget;
    setupUiItems(widget);
    widget->setStyleSheet("QLabel{font-weight:bold;}");
    widget->setFixedSize(870,400);

    dock_cache = new QDockWidget(tr("Input-Output Dock"), this);
    dock_cache->setWidget(widget);
    addDockWidget(Qt::RightDockWidgetArea, dock_cache);
    setCentralWidget(dock_cache);
}


/*Set up UI items on cache Dock Widget*/
void MainWindow::setupUiItems(QWidget *widget){

    QVBoxLayout *vmainLayout=new QVBoxLayout;
    QGridLayout *layout=new QGridLayout;

    memory_widget=new MemoryWidget;
    layout->addWidget(memory_widget,0,0);
    connect(memory_widget,SIGNAL(sim_param_changed(int,int,QString,int)),this,SLOT(UpdateMemSimParam(int,int,QString,int)));

    /*Policy and Instruction type widget*/
    policy_widget=new PolicyWidget;
    layout->addWidget(policy_widget,1,0);
    connect(policy_widget,SIGNAL(policy_rep_changed(int,bool,bool)),this,SLOT(UpdatePolicyType(int,bool,bool)));

    /*Out Param widget*/
    out_param_widget=new OutParamWidget;
    layout->addWidget(out_param_widget,0,1);

    /*Out Memory Detail in bit widget*/
    out_mem_bit_widget=new OutMemoryBitWidget;
    layout->addWidget(out_mem_bit_widget,1,1);

    connect(this,SIGNAL(sim_value_changed(int,int,QString,int)),out_mem_bit_widget,SLOT(load_change_values(int,int,QString,int)));

    QHBoxLayout *bhLayout=new QHBoxLayout;
    ActionButtonGroups(bhLayout);

    vmainLayout->addLayout(layout);
    vmainLayout->addLayout(bhLayout);
    widget->setLayout(vmainLayout);

}

/*Update In Param Values on change*/
void MainWindow::UpdateMemSimParam(int main_memory_new,int set_new,QString byte_per_block_new,int blocks_per_set_new){
    this->paramModel.t_set=set_new;
    this->paramModel.byte_per_block=byte_per_block_new.toInt();
    this->paramModel.block_per_set=blocks_per_set_new;
    this->paramModel.main_mem=main_memory_new;
    int mainM=CommonUtil::byteToBit(main_memory_new);
    int block=CommonUtil::byteToBit(byte_per_block_new.toInt());
    int tset=CommonUtil::byteToBit(set_new);
    int tag=mainM-block-tset;
    this->paramModel.tag_field_cal=tag;
    // widget_graphicII->TagValueChanged(paramModel);
    emit sim_value_changed(main_memory_new,set_new,byte_per_block_new,blocks_per_set_new);
}

/*Action Button Groups UI*/
void MainWindow::ActionButtonGroups(QHBoxLayout *bhLayout)
{
    infoLabel=new QLabel(tr("<b>**File is not selected.</b>"));
    infoLabel->setFixedWidth(200);
    CommonUiProperties::ChangeLabelProperties(infoLabel,Qt::red);

    QPushButton *btnExit= new QPushButton(tr("Exit"));
    btnExit->setStyleSheet("*{background-color:#d9534f;font-weight:bold}");

    QObject::connect(btnExit,SIGNAL(clicked()),this,SLOT(closeApp()));


    QPushButton *btnStart= new QPushButton(tr("Start"));
    btnStart->setStyleSheet("*{background-color:#5cb85c;font-weight:bold;}");
    QObject::connect(btnStart,SIGNAL(clicked()),this,SLOT(on_Submit_clickMain()));

    bhLayout->addWidget(infoLabel);
    bhLayout->addWidget(btnExit);
    bhLayout->addWidget(btnStart);
}



/*Init Input Parameter values */
void MainWindow::init_val(){
    this->paramModel.t_set=0;
    this->paramModel.block_per_set=0;
    this->paramModel.byte_per_block=0;
    this->paramModel.replace_policy=-1;
    this->paramModel.simulationType=2;
    this->paramModel.main_mem=256;
    this->paramModel.tag_field_cal=0;
}


/*Update In replacement policy and cache type changes*/
void MainWindow::UpdatePolicyType(int pol_index,bool ins,bool data){
    this->paramModel.replace_policy=pol_index;
    if(data){
        paramModel.simulationType=1;
    }else{
        paramModel.simulationType=2;
    }
}

