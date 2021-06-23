# Beispiel 1 - Hello World

Das erste Beispiel soll euch eine erste Einführung in FUSE Dateisysteme geben und deren Funktionsweise geben. Öffnet ein Terminal und navigiert in den Ordner `example1_hello_world`. Das FUSE Dateisystem befindet sich in der Datei `hello.c`. Der Code der Datei interessiert uns an diesem Punkt noch nicht. Dazu kommen wir später noch.

Erstellt zunächst ein neues Verzeichnis, in welches das Dateisystem später gemountet wird.
```
mkdir /tmp/hello
```
Um das Dateisystem zu erstellen. führe die folgenden Kommandos in dem Terminal aus.
```
cd example_hello_world
cmake .
make
```

Im Ordner `bin` wird die Datei `hello` erstellt. Diese repräsentiert das FUSE Dateisystem. Führe sie mit dem folgenden Kommando aus:
```
./bin/hello /tmp/hello -f
```
Das Dateisystem wird nun im Verzeichnis `/tmp/hello` gemountet. Die Option -f sorgt dafür, dass Debug Messages ausgegeben werden. Das Terminal ist daher blockiert.
Führt das Kommando `mount` aus. In der Ausgabe solltet ihr sehen, dass `hello` in `/tmp/hello` gemountet ist.

## Aufgaben
1. Öffne nun ein neues Terminal und navigiere wieder in den Ordner `example1_hello_world`. Führe das Programm `./openFile` aus. Dieses öffnet eine Datei in dem Verzeichnis `/tmp/hello`, und gibt deren Inhalt aus. In dem anderen Terminal sollten nur Debug Messages zu sehen sein. Navigiere in dem Terminal in das Verzeichnis `/tmp/hello` und führe dort ein paar Dateioperationen aus (ls, mkdir, touch, cp, mv, ...). Die Operationen werden nicht funktionieren, da sie nicht implementiert sind, aber in dem anderen Terminal sollten bei jedem Kommando Debug Messages ausgegeben werden.
**Frage: Welche Kommandos führen welche Operationen aus? Welche Operation wird am meisten ausgeführt?**
2. In Aufgabe 1 solltet ihr bemerkt haben, dass eine Operation besonders oft ausgeführt wird. Öffnet die Datei `hello.c` in einem Editor (geany sollte mit dem Setup-Skript installiert worden sein) und ersetzt den Code der Funktion mit `return NULL;`.
Führt nun wieder die oben beschriebenen Kommandos aus, um das Dateisystem neu zu erstellen. Führt es auch und führt Aufgabe 1 noch einmal aus.
**Frage: Was fällt euch hierbei auf?**

