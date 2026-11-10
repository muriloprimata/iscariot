#!/bin/sh
# Build the init as a static, libc-free x86_64 binary.
set -e
cd "$(dirname "$0")/.."
mkdir -p out
clang --target=x86_64-linux-gnu -O2 -static -nostdlib -ffreestanding \
-fno-stack-protector -fno-pie -fuse-ld=lld \
-I libc init/init.c -o out/init
ls -l out/init
