#!/bin/sh
# It's a build script. It builds the project.

if [ ! -f 'CMakeLists.txt' ]; then #prevent fuck ups
  echo 'script must be ran from the project'\''s root directory' >&2
  exit 1
fi

# argument parsing (no particular order)
for ARG in "$@"; do
  if [ "$ARG" = 'ninja' ]; then #Use Ninja as build tool (recommended)
    export CMAKE_GENERATOR='Ninja'
  elif [ "$ARG" = 'release' ]; then #Enable release mode (faster but cannot be debugged)
    export CMAKE_BUILD_TYPE='Release'
  elif [ "$ARG" = 'clean' ]; then #Makes a clean build by erasing all previously generated build files (try that if build fails mysteriously)
    rm -rf 'out/' 2>/dev/null || true
  fi
done

cmake . -B out -DCMAKE_EXPORT_COMPILE_COMMANDS=1 #Generates build files and lsp magic
cmake --build out -j "$(nproc)"                  #multithreaded build baby!!!!!
