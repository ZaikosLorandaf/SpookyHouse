#!/bin/sh

export CMAKE_BUILD_TYPE='MinSizeRel'

if [ ! -f './CMakeLists.txt' ]; then
  echo 'must be ran in the project'\''s main directory'
  exit 1
fi

for i in "$@"; do
  if [ "$i" = "clean" ]; then
    rm -rf build
  elif [ "$i" = "clang" ]; then
    export CC='clang'
    export CXX='clang++'
    export LDFLAGS='-flto=full -fuse-ld=lld'
  elif [ "$i" = "debug" ]; then
    export CMAKE_BUILD_TYPE='Debug'
  else
    printf "Unrecognized argument \"%s\"\n" "$i" >&2
    exit 1
  fi
done

BUILD_DIR='build'
cmake -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" -B "$BUILD_DIR" || exit 1
cd "$BUILD_DIR" || exit 1
make
