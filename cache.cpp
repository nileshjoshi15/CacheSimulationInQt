#include "cache.h"
#include<QDebug>

Cache::Cache(InputViewModel inViewModel)
{
    cache.no_of_sets=inViewModel.t_set;
    cache.block_size=inViewModel.byte_per_block;
    cache.blocks_per_set=inViewModel.block_per_set;
    cache.replace_policy=inViewModel.replace_policy;
    InitCache();
}

void Cache::InitCache(){
    qDebug()<<"Cache Initialsed";
    for(int set =0;set<cache.no_of_sets;set++){
        QList<CacheItemModel> cacheItems;
        for(int block=0;block<cache.blocks_per_set;block++){
            CacheItemModel cacheEntry;
            cacheEntry.tag=-1;
            cacheEntry.valid_bit=-1;
            cacheEntry.ref_bit=0;
            cacheEntry.t_access=-1;
            cacheEntry.t_frequency=0;
            cacheItems.append(cacheEntry);
        }
        cacheContent[set]=cacheItems;
    }
}
bool Cache::FindOrAssignMem(int set_no,int tag_no){
    QList<CacheItemModel> items= cacheContent.value(set_no);
    UpdateMemAccess(set_no);
    /*Found tag logic*/
    for(int i=0;i<cache.blocks_per_set;i++){
        if(items[i].tag==tag_no && items[i].ref_bit==1){
            cacheContent[set_no][i].t_access=0;
            cacheContent[set_no][i].t_frequency+=1;
            return true;
        }
    }
    /*Tag not found but address available logic*/
    for(int i=0;i<cache.blocks_per_set;i++){
        if(items[i].tag==-1 && items[i].ref_bit==0){
             setValues(i,set_no,tag_no);
            return false;
        }
    }
    if(cache.replace_policy==1){
        LRU_policy(set_no,tag_no);
        return false;
    }
    if(cache.replace_policy==2){
        LFU_policy(set_no,tag_no);
        return false;
    }
    if(cache.replace_policy==3){
        Random_policy(set_no,tag_no);
        return false;
    }
    return false;
}


void Cache::UpdateMemAccess(int set_no){
    for(int i=0;i<cache.blocks_per_set;i++){
        if( cacheContent[set_no][i].tag!=-1 &&  cacheContent[set_no][i].ref_bit!=-1){
            cacheContent[set_no][i].t_access+=1;
        }
    }
}

void Cache:: LRU_policy(int set_no, int tag_no){
    int max_access=cacheContent[set_no][0].t_access;
    int max_access_index=0;
    for(int i=1;i<cache.blocks_per_set;i++){
        if( cacheContent[set_no][i].t_access>max_access &&  cacheContent[set_no][i].ref_bit!=-1){
            max_access=cacheContent[set_no][i].t_access;
            max_access_index=i;
        }
    }
    setValues(max_access_index,set_no,tag_no);
}


void Cache:: LFU_policy(int set_no, int tag_no){
    int min_freq=cacheContent[set_no][0].t_frequency;
    int min_freq_index=0;
    for(int i=1;i<cache.blocks_per_set;i++){
        if( cacheContent[set_no][i].t_frequency<min_freq &&  cacheContent[set_no][i].ref_bit!=-1){
            min_freq=cacheContent[set_no][i].t_frequency;
            min_freq_index=i;
        }
    }
    setValues(min_freq_index,set_no,tag_no);
}


void Cache:: Random_policy(int set_no, int tag_no){
    srand((unsigned)time(0));
    int random_index = (rand()%cache.blocks_per_set);
    setValues(random_index,set_no,tag_no);
}

void Cache::setValues(int index,int set_no,int tag_no){
    cacheContent[set_no][index].ref_bit=1;
    cacheContent[set_no][index].set_no=set_no;
    cacheContent[set_no][index].tag=tag_no;
    cacheContent[set_no][index].t_access=0;
    cacheContent[set_no][index].valid_bit=1;
    cacheContent[set_no][index].t_frequency+=1;
}


