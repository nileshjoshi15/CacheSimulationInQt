#include<QList>
#include<QDebug>
#include<QProgressDialog>
#include<QProgressBar>
#include "fileutil.h"
#include "cache.h"
#include "setassociativememsim.h"

setAssociativeMemSim::setAssociativeMemSim(InputViewModel inParams)
{
    simModelParams=inParams;
    InitOut();
}

OutputViewModel setAssociativeMemSim::InspectMemAddr(){
    Cache cache(simModelParams);
    int t_block=simModelParams.byte_per_block;

    QList<unsigned long> mem_addresses=FileUtil::ReadTraceFileInHEX(simModelParams.file_name);
    foreach (unsigned long addr, mem_addresses) {
        //int offset_addr=addr%t_block;

        int addr_no_offset=addr/t_block;

        unsigned long tag_number=addr_no_offset/simModelParams.t_set;

        int set_number=addr_no_offset%simModelParams.t_set;

        if(cache.FindOrAssignMem(set_number,tag_number)){
            sim_out.no_hit++;
        }else{
            sim_out.no_miss++;
        }
        sim_out.mem_access++;
    }
    sim_out.compusory_miss=simModelParams.t_set*simModelParams.block_per_set;
    return sim_out;
}

void setAssociativeMemSim::InitOut(){
    sim_out.no_hit=0;
    sim_out.no_miss=0;
    sim_out.mem_access=0;
    sim_out.compusory_miss=0;
}








