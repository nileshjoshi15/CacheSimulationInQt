#ifndef CACHE_H
#define CACHE_H
#include<QHash>
#include "simmulationmodel.h"

class Cache
{
public:
    Cache(InputViewModel inViewModel);
    bool FindOrAssignMem(int set_no,int tag_no);
    QHash<int,QList<CacheItemModel> > cacheContent;

private:
    CacheModel cache;
    void InitCache();
    void UpdateMemAccess(int set_no);
    void LRU_policy(int set_no, int tag_no);
    void LFU_policy(int set_no, int tag_no);
    void Random_policy(int set_no,int tag_no);
    void setValues(int index,int set_no,int tag_no);

};

#endif // CACHE_H
