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

/**
 * TODO: Make sure to add all necessary includes here
 */

//#include "e2fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <sys/mman.h>
#include <string.h>
#include "header.h"
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>


 /**
  * TODO: Add any helper implementations here
  */

  // .....


#define CLOSE_PROGRAM 1
void ext2_fsal_init(char **image,char *, sem_t **);

struct shard
{
	sem_t *semaphore_o;
	char **input;
	char **image_o;
};

void read_n(char *arr,int max)
{
	int i=0;
	while(i<max)
	{
		int valread=read(STDIN_FILENO,arr+i,1);
		if(arr[i]=='\n')
		{arr[i]='\0';break;}

		
		i++;
	}
	//close(sock);



}

int main(int argc, char *argv[])
{
	char *image="hello";
 	char **image_global=NULL;
 	sem_t *semaphore=malloc(sizeof(sem_t));
 	//printf("%s\n",argv[2]);	
	//if(argc != 2) 
	{
	//	fprintf(stderr, "Usage: %s <image file name>\n", argv[0]);
	//	exit(1);
	}
	

	//printf("cool : = %s\n",*image_global);
	if(image == MAP_FAILED) 
	{
		perror("mmap");
		exit(1);
	}

	

	
	
	struct shard *obj=malloc(sizeof(struct shard));
	obj->semaphore_o=semaphore;
	(obj->input)=malloc(sizeof(char) *50);
	printf("p %s\n",argv[1]);
	
	while(1)
	{
		read_n(obj->input,50);
		if((obj->input)!=NULL)
		{
			if(strncmp(obj->input,"rm",2)==0)
			{

				ext2_fsal_init(&image,argv[1],&semaphore);
				sem_wait(semaphore);
				image_global=&image;

				obj->image_o=image_global;
				char *cmd=obj->input;
				cmd=cmd+3;
				ext2_fsal_rm(cmd,&image);	
				printf("rm command\n");
				sem_post(semaphore);
				sem_close(semaphore);
				exit(0);
			}
			if(strncmp(obj->input,"mkdir",strlen("mkdir"))==0)
			{
				ext2_fsal_init(&image,argv[1],&semaphore);
				sem_wait(semaphore);	
				printf("%s\n",argv[1]);
				//image_global=&image;
	                        char *p=obj->input;
	                        printf("p = %s\n",p);
				ext2_fsal_mkdir(p,&image);
				obj->image_o=image_global;
				printf("mkdir command\n");
				sem_post(semaphore);
				sem_close(semaphore);				
				exit(0);
			}	        
			if(strncmp(obj->input,"cp",2)==0)
			{
				ext2_fsal_init(&image,argv[1],&semaphore);
				sem_wait(semaphore);	
				image_global=&image;
				obj->image_o=image_global;
				char *cp=malloc(strlen(obj->input)+1);
				char *source =malloc(strlen(obj->input)+1);
				printf("%zu^\n",strlen(obj->input)+1);
				int i=0;
				cp=obj->input;
				printf("II %s\n",cp);
				cp=cp+3;
				i=0;
				while(i<strlen(cp))
				{
					printf(" - %c %c\n",source[i],cp[i]);

				        source[i]=cp[i];
					printf("%c %c\n",source[i],cp[i]);
					if(cp[i]==' ')
					{
					printf("i = %d\n",i);
					break;}
					
					i++;
				}
				cp=cp+i;
				char *dest=cp;
				i=strlen(cp);

				dest[i]='\0';
				
				printf("source = %s desk = %s %zu\n ",source,dest,strlen(dest));
				char *cmd=malloc(sizeof(char)*50);
				memcpy(cmd,"mkdir ",strlen("mkdir "));
				memcpy(cmd+strlen("mkdir "),dest,strlen(dest));
				cmd[strlen("mkdir ")+strlen(dest)+1]='\0';

				i++;
				source[i]='\0';
				ext2_fsal_cp(source,cmd,&image);
				
				
				
				printf("cp command %s\n",argv[1]);
				sem_post(semaphore);
				sem_close(semaphore);					
				exit(0);
			}
		
			
		}
		else
		{
//				printf("NULL\n");
		}	
	}

	//sem_post(semaphore1);
	
	return 0;
}	
