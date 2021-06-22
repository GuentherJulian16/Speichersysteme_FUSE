#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static const char *hello_str = "HelloWorld\n";
static const char *hello_path = "/hello";
static int counter = 1;

static void *hello_init(struct fuse_conn_info *conn,
		      struct fuse_config *cfg)
{
	printf("%.3d: DEBUG: hello from init\n", counter++);
	return NULL;
}

static int hello_access(const char *path, int mask)
{
	printf("%.3d: DEBUG: hello from access, path=%s\n", counter++, path);
	int res;

	res = access(path, mask);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_readlink(const char *path, char *buf, size_t size)
{
	printf("%.3d: DEBUG: hello from readlink, path=%s\n", counter++, path);
	int res;

	res = readlink(path, buf, size - 1);
	if (res == -1)
		return -errno;

	buf[res] = '\0';
	return 0;
}

static int hello_mkdir(const char *path, mode_t mode)
{
	printf("%.3d: DEBUG: hello from mkdir, path=%s\n", counter++, path);
	int res;

	res = mkdir(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_unlink(const char *path)
{
	printf("%.3d: DEBUG: hello from unlink, path=%s\n", counter++, path);
	int res;

	res = unlink(path);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_rmdir(const char *path)
{
	printf("%.3d: DEBUG: hello from rmdir, path=%s\n", counter++, path);
	int res;

	res = rmdir(path);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_rename(const char *from, const char *to, unsigned int flags)
{
	printf("%.3d: DEBUG: hello from rename, from=%s,to=%s\n", counter++, from, to);
	int res;

	if (flags)
		return -EINVAL;

	res = rename(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_create(const char *path, mode_t mode,
		      struct fuse_file_info *fi)
{
	printf("%.3d: DEBUG: hello from create, path=%s\n", counter++, path);
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
	printf("%.3d: DEBUG: hello from write, path=%s\n", counter++, path);
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
	printf("%.3d: DEBUG: hello from statfs, path=%s\n", counter++, path);
	int res;

	res = statvfs(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int hello_getattr(const char *path, struct stat *stbuf)
{
	printf("%.3d: DEBUG: hello from getattr, path=%s\n", counter++, path);
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
	printf("%.3d: DEBUG: hello from readdir, path=%s\n", counter++, path);
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
	printf("%.3d: DEBUG: hello from open, path=%s\n", counter++, path);
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	printf("%.3d: DEBUG: hello from read, path=%s\n", counter++, path);
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
	.create     = hello_create,
	.getattr	= hello_getattr,
	.mkdir      = hello_mkdir,
	.readdir	= hello_readdir,
	.readlink   = hello_readlink,
	.rename     = hello_rename,
	.rmdir      = hello_rmdir,
	.open		= hello_open,
	.statfs     = hello_statfs,
	.write      = hello_write,
	.read		= hello_read,
	.unlink		= hello_unlink
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &hello_oper, NULL);
}
