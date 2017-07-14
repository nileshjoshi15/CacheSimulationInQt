#ifndef COMMONUTIL_H
#define COMMONUTIL_H


class CommonUtil
{
public:
    CommonUtil();
    static unsigned long CalPow(int base,unsigned long exp);
    static int byteToBit(unsigned long byte);
};

#endif // COMMONUTIL_H
