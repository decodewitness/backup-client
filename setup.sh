#!/bin/bash

g++ -o bbckup27 main.cpp

mkdir -p bbckup27-program/DEBIAN
mkdir -p bbckup27-program/usr/bin
mkdir -p bbckup27-program/usr/share

cp control bbckup27-program/DEBIAN
cp bbckup27 bbckup27-program/usr/bin
cp Manual.odt bbckup27-program/usr/share

sudo chown -R root:root `pwd`/bbckup27-program

sudo chmod 0755 `pwd`/bbckup27-program/DEBIAN/control

dpkg -b `pwd`/bbckup27-program

sudo rm -rf bbckup27-program

exit 0
