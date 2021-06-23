#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

static int counter = 1;

static int do_getattr( const char *path, struct stat *st )
{
	printf("%.3d: DEBUG: hello from getattr, path=%s\n", counter++, path);
	
	if ( strcmp( path, "/" ) == 0 )		//wird ausgeführt wenn der Pfad das root Verzeichnis ist
	{
		st->st_mode = S_IFDIR | 0755;	//s_IFDIR = Dateityp Konstante für Verzeichnisse, 0755 = Berechtigungen
	}
	else
	{
		st->st_mode = S_IFREG | 0644;
		st->st_size = 1024;
	}
	
	return 0;
}

static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi )
{
	printf("%.3d: DEBUG: readdir called, path=%s\n", counter++, path);
	
	filler( buffer, ".", NULL, 0 );  // Aktuelles Verzeichnis
	filler( buffer, "..", NULL, 0 ); // Elternverzeichnis
	
	if ( strcmp( path, "/" ) == 0 )
	{
		filler( buffer, "myFile.txt", NULL, 0 );
		filler( buffer, "myFile.xtx", NULL, 0 );
	}
	
	return 0;
}

static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi )
{
	printf("%.3d: DEBUG: read called, path=%s\n", counter++, path);
	
	char* txtFileContent = "Hallo Welt!";
	char* text = NULL;
	
	if ( strcmp( path, "/myFile.txt" ) == 0 )
		text = txtFileContent;
	else if ( strcmp( path, "/myFile.xtx" ) == 0 )
		text = "Dateiendung nicht bekannt!";
	else
		return -1;
	
	memcpy( buffer, text + offset, size );
		
	return strlen( text ) - offset;
}

static struct fuse_operations operations = {
    .getattr	= do_getattr,
    .readdir	= do_readdir,
    .read		= do_read,
};

int main( int argc, char *argv[] )
{
	return fuse_main( argc, argv, &operations, NULL );
}
