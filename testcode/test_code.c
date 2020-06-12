#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/types.h>
int main()
{
    int fd, len;
    char inbuf[20];
    char outbuf[20] = "scull dev test! BY ZICHEN LIU";
    fd = open("/dev/scull", O_WRONLY);
    if (fd < 0)
    {
        printf("Error openning the device of sculldev for writing!/n");
        exit(1);
    }
    len = write(fd, outbuf, strlen(outbuf) + 1);
    if (len < 0)
    {
        printf("Error writing to the device!/n");
        close(fd);
        exit(1);
    }
    printf("writing %d bytes to the device!/n", len);
    close(fd);
    fd = open("/dev/scull", O_RDONLY);
    if (fd < 0)
    {
        printf("Error openning the device of sculldev for reading!/n");
        exit(1);
    }
    len = read(fd, inbuf, len);
    if (len < 0)
    {
        printf("Error reading from the device!/n ");
        close(fd);
        exit(1);
    }
    printf("reading %d bytes from the device!/n", len);
    printf("%s/n", inbuf);
}