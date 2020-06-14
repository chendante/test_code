#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "scull/scull.h"
int main()
{
    int fd, len;
    char outbuf[] = "scull dev test! BY ZICHEN LIU";
    fd = open("/dev/scull", O_WRONLY);
    if (fd < 0)
    {
        printf("Error openning the device of scull for writing!\n");
        exit(1);
    }
    len = write(fd, outbuf, strlen(outbuf) + 1);
    if (len < 0)
    {
        printf("Error writing to the device!\n");
        close(fd);
        exit(1);
    }
    printf("writing %d bytes to the device!\n", len);
    close(fd);
    fd = open("/dev/scull", O_RDWR);
    if (fd < 0)
    {
        printf("Error openning the device of scull for reading!\n");
        exit(1);
    }
    int retval, quantum = 10;

    retval = ioctl(fd, SCULL_IOCSQUANTUM, &quantum);
    close(fd);
    if (retval < 0)
    {
        printf("Error ioctl from the device!\n ");
        exit(1);
    }
    printf("ioctl retval: %d\n", retval);
    printf("%s\n", inbuf);
}