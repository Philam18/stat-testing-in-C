# stat-testing-in-C
using the stat() call in C to read directories and print crucial file information

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
