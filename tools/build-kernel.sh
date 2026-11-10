#!/bin/sh
# Build a minimal Linux kernel (tinyconfig + kernel/iscariot.config).
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
KVER="${KVER:-6.12.10}"
WORK="$ROOT/out/kernel-build"

mkdir -p "$WORK"
cd "$WORK"
if [ ! -d "linux-$KVER" ]; then
curl -fL -o linux.tar.xz \
"https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-$KVER.tar.xz"
tar xf linux.tar.xz
fi
cd "linux-$KVER"
make tinyconfig
./scripts/kconfig/merge_config.sh -m .config "$ROOT/kernel/iscariot.config"
make olddefconfig
make -j"$(nproc)" bzImage
cp arch/x86/boot/bzImage "$ROOT/out/bzImage"
ls -l "$ROOT/out/bzImage"
