#!/usr/bin/env python3
#poor poor windows users can't use POSIX shell scripts...

import subprocess

try:
    subprocess.check_call(["cmake", ".", "-B", "out", "-DCMAKE_EXPORT_COMPILE_COMMANDS=1"])
    subprocess.check_call(["cmake", "--build", "out"])
except (subprocess.CalledProcessError) as e:
    print(e)
    exit(1)
