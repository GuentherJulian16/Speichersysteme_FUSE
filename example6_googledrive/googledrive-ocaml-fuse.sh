#!/bin/bash
sudo add-apt-repository ppa:allessandro-strada/ppa
sudo apt update && sudo apt install google-drive-ocamlfuse
google-drive-ocamlfuse
if [[ ! -d "/tmp/googledrive" ]]
then
    mkdir /tmp/googledrive
fi
google-drive-ocamlfuse /tmp/googledrive
