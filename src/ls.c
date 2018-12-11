#include "../includes/ft_ls.h"

// int lstat(const char *path, struct stat *buff); -- file info
//struct stat {
//    dev_t     st_dev;     /* ID of device containing file */
//    ino_t     st_ino;     /* inode number */
//    mode_t    st_mode;    /* protection */
//    nlink_t   st_nlink;   /* number of hard links */
//    uid_t     st_uid;     /* user ID of owner */
//    gid_t     st_gid;     /* group ID of owner */
//    dev_t     st_rdev;    /* device ID (if special file) */
//    off_t     st_size;    /* total size, in bytes */
//    blksize_t st_blksize; /* blocksize for file system I/O */
//    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//    time_t    st_atime;   /* time of last access */
//    time_t    st_mtime;   /* time of last modification */
//    time_t    st_ctime;   /* time of last status change */
//};

/*S_ISREG(m)
is it a regular file?
S_ISDIR(m)
directory?
S_ISCHR(m)
character device?
S_ISBLK(m)
block device?
S_ISFIFO(m)
FIFO (named pipe)?
S_ISLNK(m)
symbolic link? (Not in POSIX.1-1996.)
S_ISSOCK(m)
socket? (Not in POSIX.1-1996.)*/

/*struct stat sb;

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

if (argc != 2) {
fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
exit(EXIT_FAILURE);
}

if (stat(argv[1], &sb) == -1) {
perror("stat");
exit(EXIT_FAILURE);
}*/

void	print_type(mode_t st_mode)
{
	int bits;

	bits = (st_mode & S_IFMT);
	if (bits == S_IFDIR)
		write(1, "d", 1);
	else if (bits == S_IFCHR)
	{
		write(1, "c", 1);
		return ;
	}
	else if (bits == S_IFBLK)
	{
		write(1, "b", 1);
		return ;
	}
	else if (bits == S_IFLNK)
		write(1, "l", 1);
	else if (bits == S_IFSOCK)
		write(1, "s", 1);
	else if (bits == S_IFIFO)
		write(1, "f", 1);
	else
		write(1, "-", 1);
}

void	print_perms(mode_t st_mode)
{
	print_type(st_mode);

	//user
    ft_printf("%c", (st_mode & S_IRUSR ? 'r' : '-')); //read
    ft_printf("%c", (st_mode & S_IWUSR ? 'w' : '-')); //write
    ft_printf("%c", (st_mode & S_IXUSR ? 'x' : '-')); //execute

    //group
    ft_printf("%c", (st_mode & S_IRGRP ? 'r' : '-')); //read
    ft_printf("%c", (st_mode & S_IWGRP ? 'w' : '-')); //write
    ft_printf("%c", (st_mode & S_IXGRP ? 'x' : '-')); //execute

    //wtf?
    ft_printf("%c", (st_mode & S_IROTH ? 'r' : '-')); //read
    ft_printf("%c", (st_mode & S_IWOTH ? 'w' : '-')); //write
    ft_printf("%c", (st_mode & S_IXOTH ? 'x' : '-')); //execute
}

void	get_file_info(t_args *meta)
{
	struct stat sb;
	struct passwd *pwd;
	struct group *gwd;
	int x;

	if ((x = lstat(meta->args[0], &sb)) == -1)
	{
		ft_printf("Error");
		return ;
	}
		ft_printf("return: %d\n", x);
		switch (sb.st_mode & S_IFMT) {
	    case S_IFBLK:  printf("block device\n");            break;
	    case S_IFCHR:  printf("character device\n");        break;
	    case S_IFDIR:  printf("directory\n");               break;
	    case S_IFIFO:  printf("FIFO/pipe\n");               break;
	    case S_IFLNK:  printf("symlink\n");                 break;
	    case S_IFREG:  printf("regular file\n");            break;
	    case S_IFSOCK: printf("socket\n");                  break;
	    default:       printf("unknown?\n");                break;
    }
    pwd = getpwuid(sb.st_uid);
    gwd = getgrgid(pwd->pw_gid);
   	ft_printf("user: %s\n", pwd->pw_name);
    ft_printf("group: %s\n", gwd->gr_name);
    ft_printf("size: %jd\n", sb.st_size);
    ft_printf("permissions: ");
    print_perms(sb.st_mode);
}

void	get_folder_info(t_args *meta)
{
    DIR *dir;
    struct dirent *dent;
    char buffer[50];

    strcpy(buffer, meta->args[0]);
    dir = opendir(buffer);   //this part
    if(dir != NULL)
    {
        while((dent = readdir(dir)) != NULL)
            ft_printf("%s\n", dent->d_name);
    }
    closedir(dir);
}

void	processor(t_args *meta)
{
	get_file_info(meta);
}

int 	main(int argc, char **argv)
{
	t_args meta;

	if (preprocessor(&meta, argv, argc) == false)
	{
		return (1);
	}
	processor(&meta);
	ft_printf("\nend");
	return (0);
}