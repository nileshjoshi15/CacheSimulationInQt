#include<QApplication>
#include<QDebug>
#include<QFile>
#include<QList>
#include "validateuival.h"
#include "errormsgcode.h"

ValidateUiVal::ValidateUiVal()
{

}

ErrorMsgCode ValidateUiVal::ValidateUI(InputViewModel model,int msgPriority){
    QFile file(model.file_name);
    ErrorMsgCode errorMsgInfo;
    //errorMsgInfo.errorMessage=QString::fromStdString("No Error Occured");
    errorMsgInfo.IsError=false;


    if(model.byte_per_block==0){
        errorMsgInfo.errorMessage.append("Byte per block should be greater than 0");
        errorMsgInfo.IsError=true;
    }

    if(model.t_set==0){
         errorMsgInfo.errorMessage.append("Total set should be greater than 0");
        errorMsgInfo.IsError=true;
    }

    if(model.tag_field_cal<=0){
        errorMsgInfo.errorMessage.append("Tag field should be greater than 0");
        errorMsgInfo.IsError=true;
    }
    if(msgPriority==1){
        if(!errorMsgInfo.IsError){
            errorMsgInfo.errorMessage.append("No Error:");
        }
        return errorMsgInfo;
    }

    if(model.block_per_set==0){
        errorMsgInfo.errorMessage.append("Blocks per set should be greater than 0");
        errorMsgInfo.IsError=true;
    }
    /*Check file selected or not*/
    if(model.file_name==NULL){
        errorMsgInfo.errorMessage.append("You have not selected trace file. Please select trace file from file menu");
        errorMsgInfo.IsError=true;
    }
    else if(!file.open(QIODevice::ReadOnly)){
        errorMsgInfo.errorMessage.append("Can not open file");
        errorMsgInfo.IsError=true;
    }

    if(model.replace_policy==-1){
        errorMsgInfo.errorMessage.append("Please select replacement policy");
        errorMsgInfo.IsError=true;
    }

    if(!errorMsgInfo.IsError){
        errorMsgInfo.errorMessage.append("No Error:");
    }
    return errorMsgInfo;
}
