#include "ADTs/arraylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define UNUSED __attribute__((unused))

int main(int UNUSED argc, char *argv[])
{
    const ArrayList *stl = ArrayList_create(0L, free);
    long i;
    char buf[BUFSIZ];

    int exitStatus = EXIT_FAILURE;

    if ((stl) == NULL)
    {
        fprintf(stderr, "%s: unable to create ArrayList\n", argv[0]);
    }

    while (fgets(buf, BUFSIZ, stdin) != NULL)
    {
        bool status = stl->add(stl, (void *)strdup(buf));
        if (!status)
        {
            fprintf(stderr, "%s: unable to append to ArrayList\n", argv[0]);
            goto cleanup;
        }
    }

    for (i = stl->size(stl) - 1; i >= 0; i--)
    {
        char *svalue;
        stl->get(stl, i, (void *)&svalue);
        printf("%s", svalue);
    }

    if (i == 0)
    {
        printf("\n");
    }

    exitStatus = EXIT_SUCCESS;

cleanup:
    stl->destroy(stl);
    return exitStatus;
}