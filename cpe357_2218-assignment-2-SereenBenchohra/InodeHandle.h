#ifndef INODEHANDLE_H
#define INODEHANDLE_H


#define VALID_ARGUMENTS 3
#define INODE_LIST_PATH "./fs/inodes_list"

void verify_arguments(int argc, char *argv[], int *maxInodes);
void is_integer(char *isNum, int *maxInodes);
void isFile(char *isFile);
void load_Inode(char *inode_fs);
void Inode_Directory_Check(char *inode_fs);
void getInode_fs_len(int *inode_fs_len);
FILE *open_file(const char *path, const char *mode);



#endif