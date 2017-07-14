#ifndef VALIDATEUIVAL_H
#define VALIDATEUIVAL_H
#include "errormsgcode.h"
#include "simmulationmodel.h"

class ValidateUiVal
{
public:
    ValidateUiVal();
    static ErrorMsgCode ValidateUI(InputViewModel model,int msgPriority);
};

#endif // VALIDATEUIVAL_H
