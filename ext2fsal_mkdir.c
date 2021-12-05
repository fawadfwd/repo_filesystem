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

//#include "ext2fsal.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header1.h"

unsigned char *disk;
int32_t ext2_fsal_mkdir(const char *path,char **image)
{

     printf("%zu %s oo\n",strlen(path),path);
    /**
     * TODO: implement the ext2_mkdir command here ...
     * the argument path is the path to the directory that is to be created.
     */
     	
     /* This is just to avoid compilation warnings, remove this line when you're done. */
     //printf("%s\n",*image_global);
     
     disk =*image;
     
    // printf("ya %s\n",disk);
    struct ext2_super_block *sb = (struct ext2_super_block *)(disk + 1024);

    //group desc pointer (bgd), starts right after super block
    struct ext2_group_desc *bgd = (struct ext2_group_desc *)(disk + 1024 * 2); 

    // block bitmap pointer 
    printf("bgd->bg_block_bitmap = %d\n",bgd->bg_block_bitmap);
    unsigned char *block_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_block_bitmap)); 

    // inode bitmap pointer 
    unsigned char *inode_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_inode_bitmap)); 
    printf("bgd->bg_inode_bitmap = %d\n",bgd->bg_inode_bitmap);

    printf("Inodes: %d\n", sb->s_inodes_count);
    printf("Blocks: %d\n", sb->s_blocks_count);

    printf("Block group:\n"); 

    printf("    block bitmap: %d\n", bgd->bg_block_bitmap); 
    printf("    inode bitmap: %d\n", bgd->bg_inode_bitmap);
    printf("    inode table: %d\n", bgd->bg_inode_table);
    printf("    free blocks: %d\n", bgd->bg_free_blocks_count);
    printf("    free inodes: %d\n", bgd->bg_free_inodes_count);
    printf("    used_dirs: %d\n", bgd->bg_used_dirs_count);
    printf("---\n");
    print_bitmap(block_bitmap, sb->s_blocks_count / 8); 
    int inodes_count=sb->s_inodes_count;
    int free_inodes=bgd->bg_free_inodes_count;
    int current_inode=inodes_count-free_inodes;

    int current_block=sb->s_blocks_count-bgd->bg_free_blocks_count;
	
    //printf("before %d\n",sb->s_inodes_count);
    if(bgd->bg_inode_table<32)
    {
	bgd->bg_inode_table=bgd->bg_inode_table+1;
	bgd->bg_free_inodes_count=bgd->bg_free_inodes_count-1;
	//incremented
	printf("inodes(s) incremented\n");

    }
    else
    {
    	printf("max inode reached\n");
   	return -1;
    }

    if((128-bgd->bg_free_blocks_count)<128)
    {
    	bgd->bg_free_blocks_count=bgd->bg_free_blocks_count-1;
	printf("block(s) incremented\n");
    	
    }	
    else{
    	printf("max blocks allocated\n");
    	return -1;
    }
 //   int ret=increment_inode_count(disk);
   

    printf("incremented blocks inodes count %d	\n",sb->s_blocks_count);
   // write_to_block(path,disk,current_block);
   
    int i=0;
    int offset=0;
    

    while(i<current_block)
    {
    	//disk=disk+EXT2_BLOCK_SIZE*i;
    	offset=EXT2_BLOCK_SIZE*i;
    	i++;
    }
    i=0;


    while(path[i]!='\0')
    {
       	*(disk+offset)=path[i];
    	offset++;
    	i++;
    }
    
    return 0;
}


int32_t ext2_fsal_rm(const char *path,char **image)
{
    /**
     * TODO: implement the ext2_rm command here ...
     * the argument 'path' is the path to the file to be removed.
     */

     /* This is just to avoid compilation warnings, remove this line when you're done. */
     
     disk =*image;
     
    // printf("ya %s\n",disk);
    struct ext2_super_block *sb = (struct ext2_super_block *)(disk + 1024);

    //group desc pointer (bgd), starts right after super block
    struct ext2_group_desc *bgd = (struct ext2_group_desc *)(disk + 1024 * 2); 

    // block bitmap pointer 
    printf("bgd->bg_block_bitmap = %d\n",bgd->bg_block_bitmap);
    unsigned char *block_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_block_bitmap)); 

    // inode bitmap pointer 
    unsigned char *inode_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_inode_bitmap)); 
    printf("bgd->bg_inode_bitmap = %d\n",bgd->bg_inode_bitmap);
    struct ext2_inode *inodes = (struct ext2_inode *) (disk + (EXT2_BLOCK_SIZE * bgd->	bg_inode_table)); 
    
    int i=0;
    int offset=0;

    int max=1024*128;
    char *temp=malloc(50);
    if(temp==NULL)
    {
    	printf("heap\n");
    	exit(1);
    }
    
    memcpy(temp,"mkdir ",strlen("mkdir "));
    memcpy(temp+strlen("mkdir "),path,strlen(path)-1);
    temp[strlen("mkdir ")+strlen(path)+1]='\0';
    //printf("PRINTING %s %zu\n",temp,strlen(temp));
    while(offset<max)
    {
    	if(strncmp(disk+offset,temp,strlen(temp))==0)
    	{
    		
    		printf("found  & removed = %.*s\n",20,disk+offset);
    		memset(disk,0,1024);
    		if(bgd->bg_free_inodes_count<32)
    		{
    			bgd->bg_free_inodes_count=bgd->bg_free_inodes_count+1;

    		}	
    		else{
    			printf("something went wrong\n");	
    		    	exit(0);
    		}
    		if(bgd->bg_inode_table>0)
    		{	bgd->bg_inode_table=bgd->bg_inode_table-1;
    			
    		}
    		else{
    			printf("something went wrong\n");
    			exit(0);
    		}
    		
    		break;
    	
    	}
      	
    
    	offset=1024*i;
    	
    	i++;
    }

    
    
    (void)path;

    return 0;
}
