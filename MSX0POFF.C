#include <STDIO.H>
#include "MSX0.H"


main(argc, argv)
int argc;
char* argv[];
{
    iotputi("host/power/off", 1);

    exit();
}

 2)
    {
        printf("usage: MSX0DIN DSK_FILE_NAME");
        exit();
    }

    unit_id = iotgeti("msx/me/id");

    iotputs("msx/me/drive/a", argv[1]);

    movmem("conf/dsk0", str_buf, 9);
    str_buf[8] = 0x30 + unit_id;
    str_buf[9] = 0x00;
    iotputs(str_buf, argv[1]);

    iotputi("conf/save", 1);

    exit();
}
