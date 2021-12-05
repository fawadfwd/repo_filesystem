#ifndef FWD
#define FWD


#include <semaphore.h>

#include <sys/sem.h>
#include <stdio.h>



extern char **image_global;

extern sem_t *semaphore;
int32_t ext2_fsal_mkdir(const char *path,char **image);
int32_t ext2_fsal_rm(const char *path,char **image);
extern unsigned char *disk;


// print bitmap helper function (TE9)


#endif
