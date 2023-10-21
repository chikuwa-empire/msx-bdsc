/*
  Copyright 2023 CHIKUWA TEIKOKU
*/
#include <STDIO.H>
#include "MSX0.H"


main()
{
    int dsk_cnt;
    char* dsk_list[32];
    int i;

    dsk_cnt = iotfind("host/media/dsk", dsk_list);

    if (dsk_cnt < 0)
    {
        printf("Processing failed.");
        exit();
    }

    if (dsk_cnt == 0)
    {
        printf("Disk image file not found.");
        exit();
    }

    for (i = 0; i < dsk_cnt; i++)
    {
        printf("%s\n", dsk_list[i]);
        free(dsk_list[i]);
    }

    printf("%u files found.", dsk_cnt);

    exit();
}
