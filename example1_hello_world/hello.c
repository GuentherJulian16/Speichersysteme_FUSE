#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";

static void *hello_init(struct fuse_conn_info *conn,
		      struct fuse_config *cfg)
{
	printf("DEBUG: hello from init\n");
	return NULL;
}

static int hello_access(const char *path, int mask)
{
	printf("DEBUG: hello from access\n");
	int res;

	res = access(path, mask);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_readlink(const char *path, char *buf, size_t size)
{
	printf("DEBUG: hello from readlink \n");
	int res;

	res = readlink(path, buf, size - 1);
	if (res == -1)
		return -errno;

	buf[res] = '\0';
	return 0;
}

static int hello_mknod(const char *path, mode_t mode, dev_t rdev)
{
	printf("DEBUG: hello from mknod \n");
	int res;

	//res = mknod_wrapper(AT_FDCWD, path, NULL, mode, rdev);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_mkdir(const char *path, mode_t mode)
{
	printf("DEBUG: hello from mkdir \n");
	int res;

	res = mkdir(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_unlink(const char *path)
{
	printf("DEBUG: hello from unlink \n");
	int res;

	res = unlink(path);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_rmdir(const char *path)
{
	printf("DEBUG: hello from rmdir \n");
	int res;

	res = rmdir(path);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_symlink(const char *from, const char *to)
{
	printf("DEBUG: hello from symlink \n");
	int res;

	res = symlink(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_rename(const char *from, const char *to, unsigned int flags)
{
	printf("DEBUG: hello from rename \n");
	int res;

	if (flags)
		return -EINVAL;

	res = rename(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_link(const char *from, const char *to)
{
	printf("DEBUG: hello from link \n");
	int res;

	res = link(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_chmod(const char *path, mode_t mode,
		     struct fuse_file_info *fi)
{
	printf("DEBUG: hello from chmod \n");
	(void) fi;
	int res;

	res = chmod(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_chown(const char *path, uid_t uid, gid_t gid,
		     struct fuse_file_info *fi)
{
	printf("DEBUG: hello from chown \n");
	(void) fi;
	int res;

	res = lchown(path, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_truncate(const char *path, off_t size,
			struct fuse_file_info *fi)
{
	printf("DEBUG: hello from truncate \n");
	int res;

	if (fi != NULL)
		res = ftruncate(fi->fh, size);
	else
		res = truncate(path, size);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_create(const char *path, mode_t mode,
		      struct fuse_file_info *fi)
{
	printf("DEBUG: hello from create \n");
	int res;

	res = open(path, fi->flags, mode);
	if (res == -1)
		return -errno;

	fi->fh = res;
	return 0;
}

static int hello_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	printf("DEBUG: hello from write \n");
	int fd;
	int res;

	(void) fi;
	if(fi == NULL)
		fd = open(path, O_WRONLY);
	else
		fd = fi->fh;
	
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	if(fi == NULL)
		close(fd);
	return res;
}

static int hello_statfs(const char *path, struct statvfs *stbuf)
{
	printf("DEBUG: hello from statfs \n");
	int res;

	res = statvfs(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_getattr(const char *path, struct stat *stbuf)
{
	printf("DEBUG: hello from getattr \n");
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, hello_path) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = sizeof hello_str - 1;
	} else
		res = -ENOENT;

	return res;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	printf("DEBUG: hello from readdir \n");
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	filler(buf, hello_path + 1, NULL, 0);

	return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi)
{
	printf("DEBUG: hello from open \n");
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	printf("DEBUG: hello from read \n");
	size_t len;
	(void) fi;
	if(strcmp(path, hello_path) != 0)
		return -ENOENT;

	len = sizeof hello_str - 1;
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, hello_str + offset, size);
	} else
		size = 0;

	return size;
}

static struct fuse_operations hello_oper = {
	.init       = hello_init,
	.access     = hello_access,
	.chmod      = hello_chmod,
	.chown      = hello_chown,
	.create     = hello_create,
	.getattr	= hello_getattr,
	.link       = hello_link,
	.mkdir      = hello_mkdir,
	.mknod      = hello_mknod,
	.readdir	= hello_readdir,
	.readlink   = hello_readlink,
	.rename     = hello_rename,
	.rmdir      = hello_rmdir,
	.open		= hello_open,
	.statfs     = hello_statfs,
	.symlink    = hello_symlink,
	.truncate   = hello_truncate,
	.unlink     = hello_unlink,
	.write      = hello_write,
	.read		= hello_read,
	
	
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &hello_oper, NULL);
}
