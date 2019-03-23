#!/bin/bash

apt-cache search libsdl2
apt-get install libsdl2-dev
apt-get install libsdl2-image-dev

unalias make
make -f MakeFile

./main
