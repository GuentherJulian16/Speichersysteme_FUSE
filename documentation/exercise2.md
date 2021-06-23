# Beispiel 2 - Big Brother File System

Das zweite Beispiel geht etwas weiter als das vorherige. Das hier gezeigte Dateisystem ist eine Implementierung des 'Big Brother File System' (eine Anspielung an 'Big Brother is watching'). Der Code ist von Joseph J. Pfeiffer von der New Mexico State University. Das entsprechende Tutorial dazu gibt es auf https://www.cs.nmsu.edu/~pfeiffer/fuse-tutorial/.
Das Dateisystem bietet etwas mehr Funktionalität als das aus Aufgabe 1. Es nimmt die Requests entgegen und gibt sie an ein darunterliegendes Verzeichnis weiter. Zusätzlich werden die Operationen in einer Datei geloggt.

Zum Erstellen des Dateisystems öffne wieder ein Terminal, navigiere in das Verzeichnis `example2-bbfs` und führe folgende Kommandos aus:
```
autoreconf -f -i
./configure
make
```

Wechsel in das Verzeichnis `example` und gebe dir mit dem Befehl `ls -lR` den Inhalt der Ordner aus. Merke dir das Ergebnis.

Mounte jetzt das Big Brother Dateisystem mit folgendem Kommando:
```
../src/bbfs rootdir mountdir
```

Das Dateisystem wird in das Verzeichnis `mountdir` gemountet. Mit dem Befehl `mount` kannst du dir dies bestätigen lassen.
Navigiere in den Ordner `mountdir` und führe in dem Order ein paar Dateioperationen aus. Erstelle zum Beispiel ein paar Verzeichnisse und Dateien. Die Operationen werden in der Datei `bbfs.log` im Ordnet `example` geloggt. Lasse dir die Datei anzeigen. Sie enthält Informationen über alle ausgeführten Operationen.

Unmounte das Dateisystem mit dem Kommando `fusermount -u /pfad/zu/deinem/mountdir` und lasse dir anschließend wieder mit `ls -lR` den kompletten Inhalt von `example` anzeigen. 
**Was fällt dir dabei auf?**
