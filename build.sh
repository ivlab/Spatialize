#!/bin/bash
#export MinVR_DIR={path to where you cloned MinVR}/MinVR/build/install/MinVR/
set -e
make
make opt
make debug
make install
