#include "stringlist.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct sldata {          /* data for each instance */
    /* you must define the instance-specific fields for each StringList */
    long capacity;
    long size;
    char **theArray;
} SLData;

/* any helper functions needed by the methods */

static void sl_destroy(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;
    /* the body of the destroy() method */
    long i;
    for (i = 0L; i < sld->size; i++)
    {
        free(sld->theArray[i]); /* free element storage */
    }
    free(sld->theArray);
    free(sld);
    free((void *)sl);
}

static bool sl_append(const StringList *sl, char *s) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the append() method - it must grow the capacity of
       the stringlist if you have run out of room */
    bool ifSpace = (sld->size < sld->capacity);
    if (!ifSpace)
    {
        size_t nbytes = sld->capacity * sizeof(char *);
        nbytes *= 2;
        char **temp = (char **)realloc(sld->theArray, nbytes);
        if (temp != NULL)
        {
            sld->theArray = temp;
            sld->capacity *= 2;
            ifSpace = true;
        }
    }
    if (ifSpace)
    {
        sld->theArray[sld->size++] = s;
    }
    return ifSpace;
}

static bool sl_get(const StringList *sl, long index, char **sptr) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the get() method */
    bool status = (index >= 0L && index < sld->size);
    if (status)
        *sptr = sld->theArray[index];
    return status;
}

static long sl_size(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the size() method */
    return sld->size;
}

static StringList template = {
    NULL, sl_destroy, sl_append, sl_get, sl_size
};

const StringList *StringList_create(long capacity)
{ /* use default if 0L */
    StringList *sl = (StringList *)malloc(sizeof(StringList));
    if (sl != NULL)
    {
        SLData *sld = (SLData *)malloc(sizeof(SLData));
        if (sld != NULL)
        {
            long cap = (capacity <= 0L) ? DEFAULT_CAPACITY : capacity;
            char **array = (char **)malloc(cap * sizeof(char **));
            if (array != NULL)
            {
                // fill in instance data
                sld->capacity = cap;
                sld->size = 0L;
                sld->theArray = array;

                // assign data and methods to instance
                *sl = template;
                sl->self = sld;
            }
            else
            {
                free(sld);
                free(sl);
                sl = NULL;
            }
        }
        else
        {
            free(sl);
            sl = NULL;
        }
    }
    return sl;
    /* the body of the constructor */
}
