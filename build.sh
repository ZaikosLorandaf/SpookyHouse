#!/bin/sh
cmake -S . -G "Unix Makefiles" -B cmake || exit 1
cd cmake || exit 1
make
