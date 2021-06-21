# Beispiel 2 - Big Brother File System

Beispiel 2 zeigt die Implementierung des 'Big Brother File System' (eine Anspielung an 'Big Brother is watching'). Der Code ist von Joseph J. Pfeiffer von der New Mexico State University. Das entsprechende Tutorial dazu gibt es auf https://www.cs.nmsu.edu/~pfeiffer/fuse-tutorial/.
Das Dateisystem nimmt die Request einfach entgegen und gibt sie an ein darunterliegendes Verzeichnis weiter. Zusätzlich werden die Operationen in einer Datei geloggt.

Zum Ausführen navigiere in das Verzeichnis `example2-bbfs` und führe folgende Kommandos aus:
```
./configure
make
```

Wechsel in den Ordner `example` und führe folgendes Kommando aus, um das Dateisystem zu starten:
```
../src/bbfs rootdir mountdir
```

Das Dateisystem wird in das Verzeichnis `mountdir` gemountet. In diesem Verzeichnis kannst du jetzt ganz normal Dateiopertationen ausführen, wie zum Beispiel Dateien oder Verzeichnisse erstellen. Jedes mal wenn eine Dateioperation in `mountdir` ausgeführt wird, dann wird die Operation in einer Datei des aktuellen Verzeichnisses geloggt.
