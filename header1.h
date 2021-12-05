#ifndef FWD
#define FWD

#include <stdio.h>
#define EXT2_BLOCK_SIZE 1024

#define    EXT2_ROOT_INO         2
/* First non-reserved inode for old ext2 filesystems */
#define EXT2_GOOD_OLD_FIRST_INO 11


/*
 * Structure of a directory entry
 */
#define EXT2_NAME_LEN 255

#define    EXT2_FT_UNKNOWN  0    /* Unknown File Type */
#define    EXT2_FT_REG_FILE 1    /* Regular File */
#define    EXT2_FT_DIR      2    /* Directory File */
#define    EXT2_FT_SYMLINK  7    /* Symbolic Link */

#define    EXT2_S_IFLNK  0xA000    /* symbolic link */
#define    EXT2_S_IFREG  0x8000    /* regular file */
#define    EXT2_S_IFDIR  0x4000    /* directory */
extern unsigned char *disk;

static struct ext2_super_block {
	unsigned int   s_inodes_count;      /* Inodes count */
	unsigned int   s_blocks_count;      /* Blocks count */
	/* Reserved blocks count is not used in the assignment. */
	unsigned int   s_r_blocks_count;    /* Reserved blocks count */
	unsigned int   s_free_blocks_count; /* Free blocks count */
	unsigned int   s_free_inodes_count; /* Free inodes count */

	/******************************************************************
	 * The rest of the ext2 superblock structure is irrelevent to the
	 * assignment, but is included below, for completeness.
	 ******************************************************************/

	unsigned int   s_first_data_block;  /* First Data Block */
	unsigned int   s_log_block_size;    /* Block size */
	unsigned int   s_log_frag_size;     /* Fragment size */
	unsigned int   s_blocks_per_group;  /* # Blocks per group */
	unsigned int   s_frags_per_group;   /* # Fragments per group */
	unsigned int   s_inodes_per_group;  /* # Inodes per group */
	unsigned int   s_mtime;             /* Mount time */
	unsigned int   s_wtime;             /* Write time */
	unsigned short s_mnt_count;         /* Mount count */
	unsigned short s_max_mnt_count;     /* Maximal mount count */
	unsigned short s_magic;             /* Magic signature */
	unsigned short s_state;             /* File system state */
	unsigned short s_errors;            /* Behaviour when detecting errors */
	unsigned short s_minor_rev_level;   /* minor revision level */
	unsigned int   s_lastcheck;         /* time of last check */
	unsigned int   s_checkinterval;     /* max. time between checks */
	unsigned int   s_creator_os;        /* OS */
	unsigned int   s_rev_level;         /* Revision level */
	unsigned short s_def_resuid;        /* Default uid for reserved blocks */
	unsigned short s_def_resgid;        /* Default gid for reserved blocks */
	/*
	 * These fields are for EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 *
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	unsigned int   s_first_ino;         /* First non-reserved inode */
	unsigned short s_inode_size;        /* size of inode structure */
	unsigned short s_block_group_nr;    /* block group # of this superblock */
	unsigned int   s_feature_compat;    /* compatible feature set */
	unsigned int   s_feature_incompat;  /* incompatible feature set */
	unsigned int   s_feature_ro_compat; /* readonly-compatible feature set */
	unsigned char  s_uuid[16];          /* 128-bit uuid for volume */
	char           s_volume_name[16];   /* volume name */
	char           s_last_mounted[64];  /* directory where last mounted */
	unsigned int   s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	unsigned char  s_prealloc_blocks;     /* Nr of blocks to try to preallocate*/
	unsigned char  s_prealloc_dir_blocks; /* Nr to preallocate for dirs */
	unsigned short s_padding1;
	/*
	 * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
	unsigned char  s_journal_uuid[16]; /* uuid of journal superblock */
	unsigned int   s_journal_inum;     /* inode number of journal file */
	unsigned int   s_journal_dev;      /* device number of journal file */
	unsigned int   s_last_orphan;      /* start of list of inodes to delete */
	unsigned int   s_hash_seed[4];     /* HTREE hash seed */
	unsigned char  s_def_hash_version; /* Default hash version to use */
	unsigned char  s_reserved_char_pad;
	unsigned short s_reserved_word_pad;
	unsigned int   s_default_mount_opts;
	unsigned int   s_first_meta_bg; /* First metablock block group */
	unsigned int   s_reserved[190]; /* Padding to the end of the block */
};
struct ext2_group_desc
{
	unsigned int   bg_block_bitmap;      /* Blocks bitmap block */
	unsigned int   bg_inode_bitmap;      /* Inodes bitmap block */
	unsigned int   bg_inode_table;       /* Inodes table block */
	unsigned short bg_free_blocks_count; /* Free blocks count */
	unsigned short bg_free_inodes_count; /* Free inodes count */
	unsigned short bg_used_dirs_count;   /* Directories count */
	/* The pad and reserved fields should be 0 for the assignment. */
	unsigned short bg_pad;
	unsigned int   bg_reserved[3];
};
struct ext2_inode {
	unsigned short i_mode;        /* File mode */
	/* Use 0 as the user id for the assignment. */
	unsigned short i_uid;         /* Low 16 bits of Owner Uid */
	unsigned int   i_size;        /* Size in bytes */
	/* You don't need to set access time for the assignment. */
	unsigned int   i_atime;       /* Access time */
	unsigned int   i_ctime;       /* Creation time */
	/* You don't need to set modification time for the assignment. */
	unsigned int   i_mtime;       /* Modification time */
	/* d_time must be set when appropriate */
	unsigned int   i_dtime;       /* Deletion Time */
	/* Use 0 as the group id for the assignment. */
	unsigned short i_gid;         /* Low 16 bits of Group Id */
	unsigned short i_links_count; /* Links count */
	unsigned int   i_blocks;      /* Blocks count IN DISK SECTORS*/
	/* You can ignore flags for the assignment. */
	unsigned int   i_flags;       /* File flags */
	/* You should set it to 0. */
	unsigned int   osd1;          /* OS dependent 1 */
	unsigned int   i_block[15];   /* Pointers to blocks */
	/* You should use generation number 0 for the assignment. */
	unsigned int   i_generation;  /* File version (for NFS) */
	/* The following fields should be 0 for the assignment.  */
	unsigned int   i_file_acl;    /* File ACL */
	unsigned int   i_dir_acl;     /* Directory ACL */
	unsigned int   i_faddr;       /* Fragment address */
	unsigned int   extra[3];
};
struct ext2_dir_entry {
	unsigned int   inode;     /* Inode number */
	unsigned short rec_len;   /* Directory entry length */
	unsigned char  name_len;  /* Name length */
	unsigned char  file_type;
	char           name[];    /* File name, up to EXT2_NAME_LEN */
};



void print_bitmap(unsigned char *bitmap, int bytes){ 
    unsigned char in_use; 
    for (int byte=0; byte < bytes; byte++){ 
        for (int bit=0; bit < 8; bit++){
            in_use = bitmap[byte] & (1 << bit);
            if (in_use){ 
                printf("1"); 
            }
            else printf("0"); 
        }
        printf(" "); 
    }
    printf("\n"); 
}

// helper function to print a single inode 
// NOTE: bitmap indexing starts at 0 but inode indexing starts at 1
void print_one_inode(struct ext2_inode *inodes, int index){
    char mode;
    if (index > 32 || index < 1){ 
        // bad index error 
        fprintf(stderr, "BAD INODE INDEX");
    }
    else{ 
        if (inodes[index-1].i_mode & EXT2_S_IFREG){ 
            mode = 'f';
        }
        else if (inodes[index-1].i_mode & EXT2_S_IFDIR){ 
            mode = 'd'; 
        }
        else if (inodes[index-1].i_mode & EXT2_S_IFLNK){ 
            mode = 'l'; 
        }
        else mode = '0'; 
    }
    
    printf("[%d] type: %c size: %d links: %d blocks: %d\n",
            index, mode, inodes[index-1].i_size, inodes[index-1].i_links_count,
            inodes[index-1].i_blocks); 
    printf("[%d] Blocks: ", index);
    
    for (int i=0; i < inodes[index-1].i_blocks / 2; i++){ 
        printf(" %d", inodes[index-1].i_block[i]);
    }
    printf("\n");
}

// given a bitmap and index into it, it will tell us if the desired bit is set
int occupied(unsigned char *bitmap, int index){ 
    /*
        index % 8 = the exact bit in the byte we are looking for
        index / 8 = gives the byte we are looking for in the bitmask
    */
    unsigned char mask = 1 << (index % 8); 
    return bitmap[index / 8] & mask; 
}

void print_dir_block(int b_num) {
    
    int byte_index = 0;
    unsigned char *block = (unsigned char *) (disk + EXT2_BLOCK_SIZE*b_num);

    while (byte_index != EXT2_BLOCK_SIZE) {
        struct ext2_dir_entry *dir_entry = (struct ext2_dir_entry *) (block + byte_index);
        char type = '0';
        if ((dir_entry->file_type & EXT2_FT_DIR) != 0) {
            type = 'd';
        } else if ((dir_entry->file_type & EXT2_FT_REG_FILE) != 0) {
            type = 'f';
        } else if ((dir_entry->file_type & EXT2_FT_SYMLINK) != 0) {
            type = 'l';
        } 
        printf("Inode: %d rec_len: %d name_len: %d type= %c name=", dir_entry->inode, dir_entry->rec_len, dir_entry->name_len, type);
        char* name = (char*) (block + byte_index + sizeof(struct ext2_dir_entry));
        int i;
        for (i = 0; i < dir_entry->name_len; i++) {
            printf("%c", name[i]);
        }
        printf("\n");
        byte_index += dir_entry->rec_len;
    }
}

void print_blocks(struct ext2_inode *inodes, unsigned char *inode_bmap, int num_inodes) {
    // print out the root directory 
    int i;
    for (i = 0; i < inodes[EXT2_ROOT_INO-1].i_blocks/2; i++) {
        printf("    DIR BLOCK NUM: %d (for inode %d)\n",inodes[EXT2_ROOT_INO-1].i_block[i], EXT2_ROOT_INO);
        print_dir_block(inodes[EXT2_ROOT_INO-1].i_block[i]);
    }
    // print out the rest of the directory (check inode 12-32, if directory, process it)
    int inode_index;
    for ((inode_index = EXT2_GOOD_OLD_FIRST_INO); inode_index < num_inodes;inode_index++) {
        if ((occupied(inode_bmap, inode_index)) && ((inodes[inode_index].i_mode & EXT2_S_IFDIR) != 0)) {
            for (i = 0; i < inodes[inode_index].i_blocks/2; i++) {
                printf("    DIR BLOCK NUM: %d (for inode %d)\n",inodes[inode_index].i_block[i], inode_index+1);
                print_dir_block(inodes[inode_index].i_block[i]);
            }
        }
    }
}

// helper to print all inodes 
void print_inodes(struct ext2_inode *inodes, unsigned char *bitmask, int inodes_count){ 
    // print root inode (second inode)
    print_one_inode(inodes, EXT2_ROOT_INO); 
    // EXT2_GOOD_OLD_FIRST_INO is the first non-reserved inode
    // PRINT ONLY NON-RESERVED INODES 
    for (int i=EXT2_GOOD_OLD_FIRST_INO; i < inodes_count; i++){
        if (occupied(bitmask, i)){ 
            print_one_inode(inodes, i+1); 
        }
    }
}

int increment_inode_count(char *disk);
int increment_block_count(char *disk);
#endif

