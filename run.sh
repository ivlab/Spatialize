#!/bin/bash
export MinVR_DIR=/home/chris/MinVR/build/install/MinVR/
set -e
make
make opt
make debug
make install
./build/Release/spatialize desktop
