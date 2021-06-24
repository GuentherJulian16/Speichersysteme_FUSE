# Beispiel 5 - SSHFS
SSHFS ist ein Userspace Dateisystem, mit dem ihr euch entfernte Rechner in euer eigenes Dateisystem einbinden könnt. Das Dateisystem benutzt das SSH File Transfer Protocol um das Remote Dateisystem zu mounten. Der Vorteil bei der Verwendung von SSHFS ist, dass man die Remote Dateien komfortabel bearbeiten kann, so als ob sie auf der lokalen Festplatte liegen würden.

Wir haben die eine Datei vorbereitet, mit der ihr SSHFS ganz einfach selbst ausprobieren könnt. Öffnet dafür ein Terminal, navigiert in das Verzeichnis `example5_sshfs` und startet das Skript File: `bash sshfs.sh`.
Das Skript installiert die benötigten SSHFS Packages, erstellt das Verzeichnis `/tmp/sshfs` und fragt euch anschließend nach dem Benutzer- und Rechnernamen für die SSH-Verbindung. Danach wird das Dateisystem in `/tmp/sshfs` gemountet.
