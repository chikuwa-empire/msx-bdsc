#include <STDIO.H>
#include "MSX0.H"


main(argc, argv)
int argc;
char* argv[];
{
    int cpu_rate;
    char str_buf[20];

    cpu_rate = iotgeti("msx/me/pm/cpu/percent");

    if (argc < 2)
    {
        printf("CPU RATE: %d\%",cpu_rate);
        exit();
    }

    cpu_rate = atoi(argv[1]);

    iotputi("msx/me/pm/cpu/percent", cpu_rate);

    exit();
}
id;
    str_buf[9] = 0x00;
    iotputs(str_buf, argv[1]);

    iotputi("conf/save", 1);

    exit();
}
