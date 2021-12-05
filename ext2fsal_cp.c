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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



int32_t ext2_fsal_cp(const char *src,
                     const char *dst,char **image)
{
    /**
     * TODO: implement the ext2_cp command here ...
     * Arguments src and dst are the cp command arguments described in the handout.
     */

     /* This is just to avoid compilation warnings, remove these 2 lines when you're done. */
    (void)src;
    (void)dst;
    unsigned char *disk;
    disk=*image;
    
    int i=0;
    int offset=0;
  
    int max=1024*128;
    while(offset<max)
    {
    	if(strncmp(disk+offset,dst+1,strlen(dst))-3==0)
    	{
    		
    		printf("found directory = %.*s\n",20,disk+offset);
    		memcpy(disk+offset,src,sizeof(src)-2);
    		break;
    	
    	}
      	
    
    	offset=1024*i;
    	
    	i++;
    }
    i=0;

    return 0;
}
