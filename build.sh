#!/bin/sh
BUILD_DIR='build'
cmake -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -B "$BUILD_DIR" || exit 1
cd "$BUILD_DIR" || exit 1
make
