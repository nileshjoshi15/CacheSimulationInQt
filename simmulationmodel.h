#ifndef SIMMULATIONMODEL_H
#define SIMMULATIONMODEL_H
#include<QApplication>
#include<QHash>

struct InputViewModel{
    unsigned long main_mem;
    int simulationType;         /*1 data,2 instruction*/
    int replace_policy;         /*-1 invalid,1 LRU, 2 LFU, 3 Random*/
    int t_set;
    int block_per_set;
    int byte_per_block;
    QString file_name;
    int tag_field_cal;
};
struct CacheItemModel{
    unsigned long tag;
    int set_no;
    int ref_bit;
    int valid_bit;
    int t_access;
    int t_frequency;

};

struct OutputViewModel{
    int no_hit;
    int no_miss;
    int mem_access;
    int compusory_miss;
};

struct CacheModel{
    int no_of_sets;
    int blocks_per_set;
    int block_size;
    int replace_policy;
};




#endif // SIMMULATIONMODEL_H
