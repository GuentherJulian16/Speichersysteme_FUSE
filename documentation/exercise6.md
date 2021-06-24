# Beispiel 6 - google-drive-ocamlfuse
google-drive-ocamlfuse ist ein FUSE Dateisytem, mit dem ihr euch Google Drive Accounts in euer Dateisystem einbinden könnt. Das Dateisystem ist in OCaml programmiert.

Auch für dieses Beispiel haben wir dir eine Skriptdatei vorbereitet. Öffnet ein Terminal, navigiert in das Verzeichnis `example6_googledrive` und startet diese: `bash googledrive-ocaml-fuse.sh`
Das Skript muss zweimal ausgeführt werden. Bei der ersten Ausführung wird das Kommando `google-drive-ocamlfuse` ausgeführt, welches bei der ersten Ausführung den Browser öffnet. Dort müsst ihr eure Gmail-Daten angeben und eine Berechtigung eintragen. Bei der zweiten Ausführung wird das Dateisystem dann in `/tmp/googledrive` gemountet. Ihr könnt dann auf eure Google Drive Dateien zugreifen, wie auf lokale Dateien auch.
