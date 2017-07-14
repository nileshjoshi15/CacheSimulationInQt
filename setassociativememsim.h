#ifndef SETASSOCIATIVEMEMSIM_H
#define SETASSOCIATIVEMEMSIM_H
#include "simmulationmodel.h"

class setAssociativeMemSim
{
public:
    setAssociativeMemSim(InputViewModel inParams);
    OutputViewModel InspectMemAddr();

private:
    InputViewModel simModelParams;
    OutputViewModel sim_out;
    void InitOut();
};

#endif // SETASSOCIATIVEMEMSIM_H
