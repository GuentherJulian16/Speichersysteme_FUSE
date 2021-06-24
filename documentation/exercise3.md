# Beispiel 3 - Mein FUSE Dateisystem Part 1

In diesem Beispiel wirst du zum ersten Mal selbst ein wenig programmieren. Die Aufgabe orientiert sich an diesem Blog Artikel: http://www.maastaar.net/fuse/linux/filesystem/c/2016/05/21/writing-a-simple-filesystem-using-fuse/

Das Dateisystem wird ein Read-Only Dateisystem. Es wird zwei Dateien enthalten die der Benutzer öffnen und dessen Inhalt lesen kann. Ihr werdet das Dateisystem Schritt für Schritt implementieren. Eine Lösung findet ihr in dem Ordner `solution`.

### Aufgaben
1. Öffnet zunächst das Verzeichnis `example3_my_fuse_read` und öffnet dort die Datei `my_fuse_read.c` in einem Editor. Die Funktion 'do_getattr' ist bereits implementiert. Die anderen beiden Funktionen, die wir benötigen sind `do_read` und `do_readdir`. Erzeuge die beiden Funktionen und füge alle drei Funktionen der `operations` Struktur hinzu.
Die beiden Funktionen haben folgende Signaturen:
```
static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi )
static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi )
```
2. Die Funktion `do_readdir` benötigen wir zum Anzeigen der Dateien. Daher implementieren wir diese zuerst. Die Funktion besitzt fünf Parameter. Uns interessieren in diesem Fall die ersten drei.
* path: Pfad des angefragten Verzeichnisses
* buffer: Buffer in den die verfügbaren Dateien/Verzeichnisse geschrieben werden
* filler: Eine von FUSE bereitgestellt Funktion zum Füllen des Buffers
Wir füllen den Buffer zunächst mit Hilfe des `filler` mit zwei Einträgen, die das aktuelle Verzeichnis und das Elternverzeichnis repräsentieren:
```
filler( buffer, ".", NULL, 0 );  // Aktuelles Verzeichnis
filler( buffer, "..", NULL, 0 ); // Elternverzeichnis
```
Als nächste wollen wir die beiden Dateien erstellen. Wir überprüfen, ob der Pfad in der Anfrage das Root Verzeichnis ist. Ist dies der Fall, benutzen wir den Filler um den Buffer mit zwei weiteren Dateien zu füllen. Erzeuge hier die beiden Dateien `myFile.xtx` und `myFile.xtx`.
```
if ( strcmp( path, "/" ) == 0 )
{
	filler( buffer, "...", NULL, 0 );
	...
}
```
Du kannst das Dateisystem jetzt schon ausprobieren. Führe zum Erstellen wieder folgende Kommandos aus:
```
cmake .
make
```
Erstelle ein Verzeichnis und mounte das Dateisystem. Wenn du nun `ls` in einem Terminal in dem Verzeichnis ausführst, solltest du die beiden Dateien sehen (bei `ls -a` vier Einträge).
3. Nun müssen wir noch die Funktion `do_read` implementieren. Als erstes deklarieren wir zwei Variablen.
```
char* yourVariable = "...";
char* text = NULL;
```
Die erste repräsentiert den Text unserer Textdatei. Fülle diese mit einem beliebigen Text. Die zweite wird im nächsten Schritt zugewiesen. Sie wird deshalb mit `NULL` initialisiert.
Als nächstes machen wir eine Fallunterscheidung anhand des übergebenen Pfades und füllen je nach Pfad die Variable `text` mit dem Inhalt aus dem vorherigen Schritt oder mit dem Text 'Dateiendung nicht bekannt!'.
```
if ( strcmp( path, "/nameOfYourFirstFile" ) == 0 )
	text = yourVariable;
else if ( strcmp( path, "/nameOfYourSecondFile" ) == 0 )
	text = "Dateiendung nicht bekannt!";
else
	return -1;
```
Abschließend kopieren wir den Text in `buffer` und geben die Anzahl an Bytes zurück, die gelesen wurden.
```
memcpy( buffer, text + offset, size );
return strlen( text ) - offset;
```
Das Dateisystem ist fertig und kann nun getestet werden. Erstelle es ein weiteres Mal, wie oben beschrieben, mounte es in ein Verzeichnis und lasse dir den Inhalt der beiden Dateien ausgeben

