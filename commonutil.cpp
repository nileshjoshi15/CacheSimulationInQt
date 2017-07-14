#include "commonutil.h"
#include<QDebug>
CommonUtil::CommonUtil()
{

}

unsigned long CommonUtil::CalPow(int base,unsigned long exp){
    if(exp==0)
        return 1;
    return  base*CalPow(base,exp-1);
}
int CommonUtil:: byteToBit(unsigned long byte){
    if(byte==0){
        return 0;
    }
    int initBit=1;
    while(1){
        if(CalPow(2,initBit)>=byte){
            break;
        }
        initBit+=1;
    }
    return initBit;
}

