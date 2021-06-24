#define FUSE_USE_VERSION 29

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
    printf("%.3d: DEBUG: do_getattr called, path=%s\n", counter++, path);
	
    if ( strcmp( path, "/" ) == 0 )		//wird ausgeführt wenn der Pfad das root Verzeichnis ist
    {
        st->st_mode = S_IFDIR | 0755;	//S_IFDIR = Dateityp Konstante für Verzeichnisse, 0755 = Berechtigungen
    }
    else
    {
        st->st_mode = S_IFREG | 0644;	//s_IFREG = Dateityp einer regulären Datei
        st->st_size = 1024;
    }
	
    return 0;
}

static struct fuse_operations operations = {

};

int main( int argc, char *argv[] )
{
    return fuse_main( argc, argv, &operations, NULL );
}
