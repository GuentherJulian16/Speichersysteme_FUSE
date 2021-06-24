# Beispiel 4 - Mein FUSE Dateisystem Part 2

In diesem Beispiel werden wir unser FUSE Filesystem aus Aufgabe 3 so erweitern, dass auch Dateien und Verzeichnisse geschrieben werden können. Wir haben den Code schon so weit vorbereitet, dass das Erstellen von Verzeichnissen möglich ist. Euro Aufgabe ist es den Code so zu erweitern, dass auch Dateien geschrieben werden können. Eine Lösung finde ihr auch hier wieder in dem Ordner `solution`.

Zunächst eine kleine Erklärung zu dem bestehenden Code. Die Dateien (+ deren Inhalte) und Verzeichnisse werden in zweidimensionalen Arrays gespeichert.
```
char files[256][256];
char content[256][256];
int currentIndex = 0;

char dirs[256][256];
int currentIndexDirs = 0;
```
Beim Erstellen eines neues Verzeichnisses wird die Funktion `do_mkdir` aufgerufen, welche nichts anderes macht als dem übergebenen Pfad in dem Array zu speichern.
```
static int do_mkdir(const char *path, mode_t mode) {
	printf("%.3d: DEBUG: do_mkdir called, path=%s\n", counter++, path);
    path++;
    strcpy(dirs[currentIndexDirs++], path);
    return 0;
}
```
Beim Lesen wird in der Funktion `do_readdir` über die Arrays der Dateien und Verzeichnisse iteriert und die Pfad- bzw. Dateinamen werden in den Buffer geschrieben.
```
...
if ( strcmp( path, "/" ) == 0 )
	{
		for(int i = 0; i < currentIndex; i++) {
            filler(buffer, files[i], NULL, 0);
        }

        for(int i = 0; i < currentIndexDirs; i++) {
            filler(buffer, dirs[i], NULL, 0);
        }
	}
...
```

In der `do_init` Funktion wurden bereits zwei Dateien und ein Verzeichnis hinzugefügt. Erstellt das FUSE Dateisysteme mit den Kommandos `cmake .` und `make` und mountet es. Lasst euch mit `ls` den Inhalt des Verzeichnisses und mit `cat` den Inhalt der Dateien anzeigen. Ihr könnt auch bereits, wie oben erwähnt, neue Verzeichnisse mit `mkdir` anlegen.

### Aufgaben
Eure Aufgabe ist es nun das Schreiben von Dateien zu ermöglichen. Dafür werden die Operationen `mknod` und `write` benötigt.
1. Als erstes muss die Operation `mknod` zum Erstellen von Dateien implementiert werden. Fügt diese dem `struct fuse_operations` hinzu und erstellt die Funktion. Die Funktion hat folgende Signatur:
```
static int mknod(const char *path, mode_t mode, dev_t rdev)
```
Implementiert nun die Funktion. Diese soll den übergebenen Pfad in dem Array für die Dateien speichern und einen Eintrag in dem Array für die Dateiinhalte erstellen. Ihr könnt euch dabei an der `do_mkdir` und der `do_init` Funktion orientieren.
2. Im zweiten Schritt implementiert ihr die Funktion `write`. Diese besitzt folgende Signatur:
```
static int write(const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *info)
```
Implementiert die Funktion. Zunächst müsst ihr den Index der Datei in dem Array herausfinden. Benutzt dafür die `get_file_index` Funktion. Anschließend müsst ihr in dem Array für die Dateiinhalte den Wert an diesem Index mit dem übergebenen `buffer` überschreiben.

Erstellt euer Dateisystem neu und mountet es. Erstellt mit `echo DeinText >> DeineDatei.txt` eine neue Datei und lasst euch danach den Inhalt ausgeben.

