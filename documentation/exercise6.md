# Beispiel 6 - google-drive-ocamlfuse
google-drive-ocamlfuse ist ein FUSE Dateisytem, mit dem ihr euch Google Drive Accounts in euer Dateisystem einbinden könnt. Das Dateisystem ist in OCaml programmiert.

Auch für dieses Beispiel haben wir dir eine Skriptdatei vorbereitet. Öffnet ein Terminal, navigiert in das Verzeichnis `example6_googledrive` und startet diese: `bash googledrive-ocaml-fuse.sh`
Das Skript führt das Kommando `google-drive-ocamlfuse` aus, welches bei der ersten Ausführung den Browser öffnet. Dort müsst ihr eure Gmail-Daten angeben und eine Berechtigung eintragen. Dann führt es das Kommando noch einmal aus. Das Dateisystem wird dann in `/tmp/googledrive` gemountet. Ihr könnt dann auf eure Google Drive Dateien zugreifen, wie auf lokale Dateien auch.
