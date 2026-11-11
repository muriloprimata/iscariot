#!/bin/sh
# Build a minimal Linux kernel (tinyconfig + kernel/iscariot.config).
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
WORK="$ROOT/out/kernel-build"
BASE="https://cdn.kernel.org/pub/linux/kernel/v6.x"

# Newest 6.12.y (LTS) unless KVER is set.
if [ -z "$KVER" ]; then
KVER=$(curl -fsSL "$BASE/" \
| grep -o 'linux-6\.12\.[0-9]*\.tar\.xz' \
| sed 's/linux-//; s/\.tar\.xz//' \
| sort -V | tail -1)
fi
echo "Kernel version: $KVER"

# GCC 15 defaults to C23 and breaks old boot code: prefer GCC 14.
CCBIN=$(command -v gcc-14 || echo gcc)
echo "Compiler: $CCBIN"

mkdir -p "$WORK"
cd "$WORK"
if [ ! -d "linux-$KVER" ]; then
curl -fL -o linux.tar.xz "$BASE/linux-$KVER.tar.xz"
tar xf linux.tar.xz
fi
cd "linux-$KVER"
make CC="$CCBIN" HOSTCC="$CCBIN" tinyconfig
./scripts/kconfig/merge_config.sh -m .config "$ROOT/kernel/iscariot.config"
make CC="$CCBIN" HOSTCC="$CCBIN" olddefconfig
make CC="$CCBIN" HOSTCC="$CCBIN" -j"$(nproc)" bzImage
cp arch/x86/boot/bzImage "$ROOT/out/bzImage"
[ -s "$ROOT/out/bzImage" ] || { echo "ERROR: bzImage was not produced"; exit 1; }
ls -l "$ROOT/out/bzImage"
