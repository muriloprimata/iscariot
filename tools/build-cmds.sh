#!/bin/sh
# Build every program in shell/ and cmds/ into out/bin/.
set -e
cd "$(dirname "$0")/.."
mkdir -p out/bin
for src in shell/*.c cmds/*.c; do
[ -f "$src" ] || continue
name=$(basename "$src" .c)
clang --target=x86_64-linux-gnu -O2 -static -nostdlib -ffreestanding \
-fno-stack-protector -fno-pie -fuse-ld=lld \
-I libc "$src" -o "out/bin/$name"
echo "built out/bin/$name"
done
