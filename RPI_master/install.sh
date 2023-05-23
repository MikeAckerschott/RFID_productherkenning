#!/bin/bash
sudo apt-get update
sudo apt install git
git clone https://github.com/MikeAckerschott/RFID_productherkenning.git
sudo apt install make
sudo apt install cmake
sudo apt-get install build-essential
sudo apt-get install libwxgtk3.0-gtk3-dev
cd ~/
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
tar zxvf bcm2835-1.71.tar.gz
cd bcm2835-1.71
./configure
make
sudo make check
sudo make install
cd ~/RFID_productherkenning/
mkdir ./RPI_master/build && cd ./RPI_master/build/
cmake ../
make -j4
