#include "header1.h"


int get_current_free_inode(char *disk)
{
	struct ext2_super_block *sb = (struct ext2_super_block *)(disk + 1024);

    //group desc pointer (bgd), starts right after super block
	struct ext2_group_desc *bgd = (struct ext2_group_desc *)(disk + 1024 * 2); 

    // block bitmap pointer 
	printf("bgd->bg_block_bitmap = %d\n",bgd->bg_block_bitmap);
	unsigned char *block_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_block_bitmap)); 

    // inode bitmap pointer 
	unsigned char *inode_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_inode_bitmap)); 
	return bgd->bg_free_blocks_count;
	
}
/*int get current_free_block(char *disk)
{
	struct ext2_super_block *sb = (struct ext2_super_block *)(disk + 1024);

    //group desc pointer (bgd), starts right after super block
	struct ext2_group_desc *bgd = (struct ext2_group_desc *)(disk + 1024 * 2); 

    // block bitmap pointer 
	printf("bgd->bg_block_bitmap = %d\n",bgd->bg_block_bitmap);
	unsigned char *block_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_block_bitmap)); 

    // inode bitmap pointer 
	unsigned char *inode_bitmap = (unsigned char *) (disk + (EXT2_BLOCK_SIZE * bgd->bg_inode_bitmap)); 

}*/

int write_to_block(char **path,char *disk,int current_block)
{
	

}
