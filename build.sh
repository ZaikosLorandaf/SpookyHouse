#!/bin/sh

CMAKE_BUILD_TYPE='MinSizeRel'

if [ ! -f './CMakeLists.txt' ]; then
  echo 'must be ran in the project'\''s main directory'
  exit 1
fi

for i in "$@"; do
  if [ "$i" = "clean" ]; then
    rm -rf build
  elif [ "$i" = "debug" ]; then
    CMAKE_BUILD_TYPE='Debug'
    export CFLAGS='-fsanitize=undefined'
  elif [ "$i" = "verbose" ]; then
    export VERBOSE=1
  else
    printf "Unrecognized argument \"%s\"\nKnown arguments are:\n" "$i" >&2
    echo "clean debug verbose" | xargs printf '\t%s\n' >&2
    exit 1
  fi
done

BUILD_DIR='build'
cmake -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" -B "$BUILD_DIR" || exit 1
cd "$BUILD_DIR" || exit 1
make -j
