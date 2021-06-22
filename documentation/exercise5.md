# Beispiel 5 - SSHFS
SSHFS ist ein Userspace Dateisystem, mit dem du dir entfernte Rechner in dein eigenes Dateisystem einbinden kannst. Das Dateisystem benutzt das SSH File Transfer Protocol um das Remote Dateisystem zu mounten. Der Vorteil bei der Verwendung von SSHFS ist, dass man die Remote Dateien komfortabel bearbeiten kann, so als ob sie auf der lokalen Festplatte liegen würden.

Wir haben die eine Datei vorbereitet, mit der du SSHFS ganz einfach selbst ausprobieren kannst. Öffne dafür ein Terminal, navigiere in das Verzeichnis `example5_sshfs` und starte das Skript File: `bash sshfs.sh`.
Das Skript installiert die benötigten SSHFS Packages, erstellt das Verzeichnis `/tmp/sshfs` und fragt dich anschließend nach dem Benutzer- und Rechnernamen für die SSH-Verbindung. Danach wird das Dateisystem in `/tmp/sshfs` gemountet.
