#ifndef _STRINGLIST_H_
#define _STRINGLIST_H_

#include <stdbool.h>

/* 
 * interface to a StringList ADT 
 */
#define DEFAULT_CAPACITY 50L /* default initial capacity */

typedef struct stringlist StringList;               /* define synonym */
const StringList *StringList_create(long capacity); /* use default if 0 */

struct stringlist
{
    void *self;
    /* 
 * destroy the StringList, invoking free() on each element 
 */
    void (*destroy)(const StringList *sl);
    /* 
 * append string (allocated from the heap) to the StringList 
 */
    bool (*append)(const StringList *sl, char *s);
    /* 
 * retrieve string at `index’ from the StringList 
 */
    bool (*get)(const StringList *sl, long index, char **sptr);
    /* 
 * return the number of strings in the list, N; 
 * legal indices: index < N 
 */
    long (*size)(const StringList *sl);
};
#endif /* _STRINGLIST_H_ */