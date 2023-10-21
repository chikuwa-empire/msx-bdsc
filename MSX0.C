/*
  Copyright 2023 CHIKUWA TEIKOKU
*/
#include <STDIO.H>
#include "MSX0.H"


int sendnode(p_path)
char* p_path;
{
    int i, l;

    l = strlen(p_path);

    outp(IOT_PORT, 0xE0);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x53);
    outp(IOT_PORT, 0xC0);

    outp(IOT_PORT, l);
    for (i = 0; i < l; i++)
    {
        outp(IOT_PORT, p_path[i]);
    }
    outp(IOT_PORT, 0x00);

    return inp(IOT_PORT);
}

int iotfindc(p_path)
char* p_path;
{
    int ret;
    char r[2];

    if (sendnode(p_path) != 0)
    {
        printf("The specified device was not found.\n");
        printf("%s\n", p_path);
        return -1;
    }

    outp(IOT_PORT, 0xE0);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x11);
    outp(IOT_PORT, 0x80);
    inp(IOT_PORT);

    r[0] = inp(IOT_PORT);
    r[1] = inp(IOT_PORT);

    movmem(r, &ret, 2);

    return ret;
}

int iotfind(p_path, p_list)
char* p_path;
char** p_list;
{
    int count, i, r, l;

    count = iotfindc(p_path);

    if (sendnode(p_path) != 0)
    {
        printf("The specified device was not found.\n");
        printf("%s\n", p_path);
        return -1;
    }

    outp(IOT_PORT, 0xE0);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x13);
    outp(IOT_PORT, 0x80);

    for (r = 0; r < count; r++)
    {
        l = inp(IOT_PORT);

        p_list[r] = alloc(l + 1);

        for (i = 0; i < l; i++)
        {
            p_list[r][i] = inp(IOT_PORT);
        }
        p_list[r][l] = 0x00;
    }

    return count;
}

int iotgeti(p_path)
char * p_path;
{
    char r[2];
    int ret;

    if (sendnode(p_path) != 0)
    {
        printf("The specified device was not found.\n");
        printf("%s\n", p_path);
        return -1;
    }

    outp(IOT_PORT, 0xE0);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x80);

    inp(IOT_PORT);
    r[0] = inp(IOT_PORT);
    r[1] = inp(IOT_PORT);

    movmem(r, &ret, 2);

    return ret;
}

int iotgets(p_path, p_str)
char* p_path;
char* p_str;
{
    int i, l;

    if (sendnode(p_path) != 0)
    {
        printf("The specified device was not found.\n");
        printf("%s\n", p_path);
        return -1;
    }

    outp(IOT_PORT, 0xE0);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x03);
    outp(IOT_PORT, 0x80);

    l = inp(IOT_PORT);
    for (i = 0; i < l; i++)
    {
        p_str[i] = inp(IOT_PORT);
    }
    p_str[l] = 0x00;

    return l;
}

int iotputi(p_path, val)
char* p_path;
int val;
{
    char p[2];

    if (sendnode(p_path) != 0)
    {
        printf("The specified device was not found.\n");
        printf("%s\n", p_path);
        return -1;
    }

    outp(IOT_PORT, 0xE0);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x41);
    outp(IOT_PORT, 0xC0);

    outp(IOT_PORT, 2);
    movmem(&val, p, 2);
    outp(IOT_PORT, p[0]);
    outp(IOT_PORT, p[1]);

    return inp(IOT_PORT);
}

int iotputs(p_path, p_str)
char* p_path;
char* p_str;
{
    int i, l;

    if (sendnode(p_path) != 0)
    {
        printf("The specified device was not found.\n");
        printf("%s\n", p_path);
        return -1;
    }

    outp(IOT_PORT, 0xE0);
    outp(IOT_PORT, 0x01);
    outp(IOT_PORT, 0x43);
    outp(IOT_PORT, 0xC0);

    l = strlen(p_str);
    outp(IOT_PORT, l);
    for (i = 0; i < l; i++)
    {
        outp(IOT_PORT, p_str[i]);
    }
    outp(IOT_PORT, 0);

    return inp(IOT_PORT);
}
