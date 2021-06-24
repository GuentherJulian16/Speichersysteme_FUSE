# Beispiel 2 - Big Brother File System

Das zweite Beispiel geht etwas weiter als das Vorherige. Das hier gezeigte Dateisystem ist eine Implementierung des 'Big Brother File System' (eine Anspielung an 'Big Brother is watching'). Der Code ist von Joseph J. Pfeiffer von der New Mexico State University. Das entsprechende Tutorial dazu gibt es auf https://www.cs.nmsu.edu/~pfeiffer/fuse-tutorial/.
Das Dateisystem bietet etwas mehr Funktionalität als das aus Aufgabe 1. Es nimmt die Requests entgegen und gibt sie an ein darunterliegendes Verzeichnis weiter. Zusätzlich werden die Operationen in einer Datei geloggt.

Zum Erstellen des Dateisystems öffnet wieder ein Terminal, navigiert in das Verzeichnis `example2-bbfs` und führt folgende Kommandos aus:
```
autoreconf -f -i
./configure
make
```

Wechsel in das Verzeichnis `example` und gebt euch mit dem Befehl `ls -lR` den Inhalt der Ordner aus. Merkt euch das Ergebnis.

Mountet jetzt das Big Brother Dateisystem mit folgendem Kommando:
```
../src/bbfs rootdir mountdir
```

Das Dateisystem wird in das Verzeichnis `mountdir` gemountet. Mit dem Befehl `mount` könnt ihr euch dies bestätigen lassen.
Navigiert in den Ordner `mountdir` und führt in dem Order ein paar Dateioperationen aus. Erstellt zum Beispiel ein paar Verzeichnisse und Dateien. Die Operationen werden in der Datei `bbfs.log` im Ordner `example` geloggt. Lasst euch die Datei anzeigen. Sie enthält Informationen über alle ausgeführten Operationen.

Unmountet das Dateisystem mit dem Kommando `fusermount -u /pfad/zu/deinem/mountdir` und lasst euch anschließend wieder mit `ls -lR` den kompletten Inhalt von dem Verzeichnis `example` anzeigen. 
**Was fällt dir dabei auf?**
