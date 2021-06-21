#!/bin/bash
sudo apt-get install sshfs
if [[ ! -d "/tmp/sshfs" ]]
then
    mkdir /tmp/sshfs
fi
echo "Username:"
read username
echo "Rechnername:"
read rechnername
sshfs $username@$rechnername:/ /tmp/sshfs

