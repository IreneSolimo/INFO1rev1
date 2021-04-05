#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void crear_archivo (char * filename, mode_t mode);

int main ()
{
    crear_archivo ("arch1", 0742);
    crear_archivo ("arch2", 0564);
    crear_archivo ("arch3", 0413);
    return 0;
}

void crear_archivo (char * filename, mode_t mode)
{
    umask (00);
    int fd = open (filename, O_WRONLY | O_CREAT, mode);
    close (fd);
}