#Example 1

Öffne ein Terminal und erstelle ein neues Verzeichnis `/tmp/hello`, in das das Dateisystem gemountet wird.
```
mkdir /tmp/hello
```

Erstelle das FUSE Dateisystem.
```
cmake .
make
./bin/hello /tmp/hello -d -f
```

öffne ein neues Terminal in dem Verzeichnis, in dem das Programm `openFile` liegt. Führe die Datei aus.
```
./openFile
```


