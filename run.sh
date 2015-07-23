#!/bin/bash
if [ -z "$1" ]; then
	./build/Release/spatialize desktop
else
	./build/Release/spatialize desktop $1
fi
