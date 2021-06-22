# Beispiel 6 - google-drive-ocamlfuse
google-drive-ocamlfuse ist ein FUSE Dateisytem, mit dem du dir Google Drive Accounts in dein Dateisystem einbinden kannst. Das Dateisystem ist in OCaml programmiert.

Auch für dieses Beispiel haben wir dir eine Skriptdatei vorbereitet. Öffne ein Terminal, navigiere in das Verzeichnis `example6_googledrive` und starte diese: `bash googledrive-ocaml-fuse.sh`
Das Skript muss zweimal ausgeführt werden. Bei der ersten Ausführung wird das Kommando `google-drive-ocamlfuse` ausgeführt, welches bei der ersten Ausführung den Browser öffnet. Dort musst du deine Gmail-Daten angeben und eine Berechtigung eintragen. Bei der zweiten Ausführung wird das Dateisystem dann in `/tmp/googledrive` gemountet. Du kannst dann auf deine Google Drive Dateien zugreifen, wie auf lokale Dateien auch.
