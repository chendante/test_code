#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "scull_cmd.h"
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
    int retval, g_quantum, s_quantum=5280;

    retval = ioctl(fd, SCULL_IOCGQUANTUM, &g_quantum);
    if (retval < 0)
    {
        printf("Error ioctl from the device!\n ");
        close(fd);
        exit(1);
    }
    printf("ioctl retval: %d, g_quantum:%d\n", retval, g_quantum);
    retval = ioctl(fd, SCULL_IOCSQUANTUM, &s_quantum);
    if (retval < 0)
    {
        printf("Error ioctl from the device!\n ");
        close(fd);
        exit(1);
    }
    printf("ioctl retval: %d, s_quantum:%d\n", retval, s_quantum);
    retval = ioctl(fd, SCULL_IOCGQUANTUM, &g_quantum);
    if (retval < 0)
    {
        printf("Error ioctl from the device!\n ");
        close(fd);
        exit(1);
    }
    close(fd);
    printf("ioctl retval: %d, g_quantum:%d\n", retval, g_quantum);
}