#!/bin/sh
# Boot Iscariot in QEMU. Exit with Ctrl+A, then X.
cd "$(dirname "$0")/.."
exec qemu-system-x86_64 \
-kernel out/bzImage \
-initrd out/initramfs.cpio.gz \
-append "console=ttyS0" \
-m 128M -nographic
