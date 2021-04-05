#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (int argc, char * argv [])
{
    if (argc != 2)
    {
        printf ("Uso: %s <filename>\n", argv [0]);
        exit (0);
    }

    char * filename = argv [1];
    struct stat file_stats;

    int success = stat (filename, & file_stats);
    if (0 != success)
    {
        perror ("error en funcion stat");
    }

    printf ("ID of device containing file: %lu\n",    file_stats.st_dev);
    printf ("inode number: %lu\n",                    file_stats.st_ino);
    printf ("protection: %u\n",                       file_stats.st_mode);
    printf ("number of hard links: %lu\n",            file_stats.st_nlink);
    printf ("user ID of owner: %u\n",                 file_stats.st_uid);
    printf ("group ID of owner: %u\n",                file_stats.st_gid);
    printf ("device ID (if special file): %lu\n",     file_stats.st_rdev);
    printf ("total size, in bytes: %lu\n",            file_stats.st_size);
    printf ("blocksize for filesystem I/O: %lu\n",    file_stats.st_blksize);
    printf ("number of 512B blocks allocated: %lu\n", file_stats.st_blocks);

    return 0;
}
