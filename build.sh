#!/bin/sh
cmake -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -B cmake || exit 1
cd cmake || exit 1
make
