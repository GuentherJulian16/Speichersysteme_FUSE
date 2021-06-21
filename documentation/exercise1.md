# Beispiel 1 - Hello World

Das erste Beispiel ist ein einfaches FUSE Dateisystem, welches die Anfragen einfach an die entsprechenden System Calls durchreicht.
```
...
static int hello_mkdir(const char *path, mode_t mode)
{
	printf("DEBUG: hello from mkdir \n");
	int res;

	res = mkdir(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}
...
```

Um es auszuführen erstellt zunächst ein neues Verzeichnis, in welches das Dateisystem später gemountet wird.
```
mkdir /tmp/hello
```
Navigiere anschließend in das Verzeichnis `example1_hello_world` und erstelle das FUSE Dateisystem.
```
cd example_hello_world
cmake .
make
```

Im Ordner `bin` wird die Datei `hello` erstellt. Diese repräsentiert das FUSE Dateisystem. Führe sie mit dem folgenden Kommando aus:
```
./bin/hello /tmp/hello -d -f
```
Die Option -f sorgt dafür, dass die Debug Messages ausgegeben werden. Öffne nun ein neues Terminal und navigiere wieder in den Ordner `example1_hello_world`. Führe das Programm `./open` aus.Dieses öffnet eine Datei in dem Verzeichnis `/tmp/hello`, in dem das Dateisystem gemountet ist. In dem anderen Terminal sollten nur Debug Messages zu sehen sein.

