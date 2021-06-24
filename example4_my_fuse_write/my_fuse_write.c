#define FUSE_USE_VERSION 29

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static int counter = 1;

char files[256][256];
char content[256][256];
int currentIndex = 0;

char dirs[256][256];
int currentIndexDirs = 0;

int get_file_index( char *path) {
    path++;
    for(int i = 0; i < currentIndex; i++) {
        if(strcmp(path, files[i]) == 0)
            return i;
    }

    return -1;
}

int is_dir(const char *path) {
    path++;
    for(int i = 0; i < currentIndexDirs; i++) {
        if(strcmp(path, dirs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_file(const char *path) {
    path++;
    for(int i = 0; i < currentIndex; i++) {
        if(strcmp(path, files[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static void *do_init(struct fuse_conn_info *conn, struct fuse_config *cfg) {
    strcpy(files[currentIndex], "myFile.txt");
    strcpy(content[currentIndex++], "Hello World");

    strcpy(files[currentIndex], "myFile.xtx");
    strcpy(content[currentIndex++], "Hello World2");

    strcpy(dirs[currentIndexDirs++], "testDir");
}

static int do_getattr( const char *path, struct stat *st )
{
    printf("%.3d: DEBUG: do_getattr called, path=%s\n", counter++, path);
	
    if ( strcmp( path, "/" ) == 0 || is_dir(path) == 1 )
    {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
    }
	else if (is_file(path) == 1)
    {
        st->st_mode = S_IFREG | 0644;
        st->st_nlink = 1;
        st->st_size = 1024;
    }
    else
    {
         return -ENOENT;
    }
	
    return 0;
}

static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi )
{
    printf("%.3d: DEBUG: do_readdir called, path=%s\n", counter++, path);
	
    filler( buffer, ".", NULL, 0 );  // Aktuelles Verzeichnis
    filler( buffer, "..", NULL, 0 ); // Elternverzeichnis
	
    if ( strcmp( path, "/" ) == 0 )
    {
        for(int i = 0; i < currentIndex; i++) {
            filler(buffer, files[i], NULL, 0);
        }

        for(int i = 0; i < currentIndexDirs; i++) {
            filler(buffer, dirs[i], NULL, 0);
        }
    }
	
    return 0;
}

static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi )
{
    printf("%.3d: DEBUG: do_read called, path=%s\n", counter++, path);
	
    int index = get_file_index(path);

    if(index == -1)
        return -1;

    char* c = content[index];
	
    memcpy( buffer, c + offset, size );
		
    return strlen( c ) - offset;
}

static int do_mkdir(const char *path, mode_t mode) {
    printf("%.3d: DEBUG: do_mkdir called, path=%s\n", counter++, path);
    path++;
    strcpy(dirs[currentIndexDirs++], path);
    return 0;
}

static struct fuse_operations operations = {
    .init       = do_init,
    .getattr	= do_getattr,
    .readdir	= do_readdir,
    .read       = do_read,
    .mkdir      = do_mkdir,
};

int main( int argc, char *argv[] )
{
    return fuse_main( argc, argv, &operations, NULL );
}
