/*
 *------------
 * This code is provided solely for the personal and private use of
 * students taking the CSC369H5 course at the University of Toronto.
 * Copying for purposes other than this use is expressly prohibited.
 * All forms of distribution of this code, whether as given or with
 * any changes, are expressly prohibited.
 *
 * All of the files in this directory and all subdirectories are:
 * Copyright (c) 2019 MCS @ UTM
 * -------------
 */


//#include "e2fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "header.h"
#include <string.h>

#define SEM_NAME "/img_sem1"



void ext2_fsal_init( char** image,char *image_file,sem_t **semaphore)
{
    /**
     * TODO: Initialization tasks, e.g., initialize synchronization primitives used,
     * or any other structures that may need to be initialized in your implementation,
     * open the disk image by mmap-ing it, etc.
     */

	//image[0][0]='c';
//	memcpy(*image,"hello 7",sizeof("hello 7"));
//	printf("hello from fsal\n");
	*semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (*semaphore == SEM_FAILED) 
	{
		perror("sem_open(3) exists");
		*semaphore = sem_open(SEM_NAME,O_EXCL, S_IRUSR | S_IWUSR, 1);
		if(*semaphore == SEM_FAILED)
		{	printf("two attempts sem error\n");
			exit(EXIT_FAILURE);
		}	
		//return;

	}
	
	//sem_wait(*semaphore);
	
	int fd = open(image_file, O_RDWR);
	*image=mmap(NULL, 128 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


     
     
}

void ext2_fsal_destroy()
{
    /**
     * TODO: Cleanup tasks, e.g., destroy synchronization primitives, munmap the image, etc.
     */
}
