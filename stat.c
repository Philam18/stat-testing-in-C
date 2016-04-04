/**


The stat system call is used to retrieve information on a specific file
system in the designated directory. Information includes: file size, number of 
hard-links of file, inode reference number, device ID, user id, group id,
block size I/O, allocated blocks, last date accessed, last date modified,
and last date changed.

After the the file is opened, information is stored in a data structure, 
which in our case is named "fileStat".

To run:
	-to compile:	gcc stat.c
	-to just print out the contents of a directory, give no flag
	-run:			./a.out . (prints content of current directory)
					./a.out .. (prints content of above directory)
	-to print file stat of files in given directory, give -l flag
	-run:			./a.out . -l

**/

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//formatdate (from system time values)
//	-str date
//	-time_t val system time 
char* formatdate(char* str, time_t val)
{
	strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
	return str;
}
//stat function (imitates system call stat() )
//	-char arry[] file name string
//	-return 1 on failure to read file
int stats(char arr[]){
	struct stat fileStat;
	//stat returns a negative value on failure
	if(stat(arr,&fileStat) < 0) return 1;
	//INFO: file size
	int size = fileStat.st_size;
	//INFO: number of hard links 
	int links = fileStat.st_nlink;
	//INFO: inode reference number
	int inode = fileStat.st_ino;
	//INFO: device number
	int dev = fileStat.st_dev;
	//INFO: user id number
	int userid = fileStat.st_uid;
	//INFO: group id number
	int groupid = fileStat.st_gid;
	//INFO: block size
	int blockSize = fileStat.st_blksize;
	//INFO: number of allocated blocks
	int blocks = fileStat.st_blocks;
	//INFO: date format for access/modified/changed
	char date[100];
	printf("Information for %s\n",arr);
	printf("-------------------------------------------------------------\n");
	printf("File size: %d bytes\n",size);
	printf("Number of links: %d links\n",links);
	printf("File inode: %d\n",inode);
	printf("Device: %d\n",dev);
	printf("Ownder User ID: %d\n",userid);
	printf("Ownder Group ID: %d\n",groupid);
	printf("Blocksize I/O: %d\n",blockSize);
	printf("Allocated blocks: %d\n",blocks);
	printf("Last accessed: %s\n",formatdate(date,fileStat.st_atime));
	printf("Last modified: %s\n",formatdate(date,fileStat.st_mtime));
	printf("Last changed: %s\n",formatdate(date,fileStat.st_ctime));
/////basic format for printing file permissions (chmod) 
	printf("File Permissions: ");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
////////////////////////////////////////////////////////////////////
	printf("\n");
}

int main(int argc, char *argv[]){
	//must have at least 1 argument (directory)
	int flag = 0;
	if(argc < 2){
		return 1;
	}
	//-l flag prints file information in directory
	if(argc == 3){
		char argument[100];
		strcpy(argument, argv[2]);
		if ((strcmp(argument,"-l"))==0){
			flag = 1;
		}
	}
	//open desginated directory
	DIR *dir;
	dir = opendir(argv[1]);
	struct dirent *sd;
	//ERROR: unable to open directory
	if (dir == NULL){
		return 1;
	}
	//read contents of directory
	while( (sd=readdir(dir)) != NULL ){
		printf(">> %s\n", sd->d_name);
		if (flag == 1){
			stats(sd->d_name);
		}
	}
	return;
}





















