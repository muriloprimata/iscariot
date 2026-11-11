#!/bin/sh
# Pack rootfs/ plus the init binary into a gzip'd cpio initramfs.
set -e
cd "$(dirname "$0")/.."
[ -f out/init ] || ./tools/build-init.sh
rm -rf out/root
mkdir -p out/root
cp -a rootfs/. out/root/
find out/root -name .gitkeep -delete
cp out/init out/root/init
chmod +x out/root/init
(cd out/root && find . | cpio -o -H newc 2>/dev/null) | gzip -9 > out/initramfs.cpio.gz
ls -l out/initramfs.cpio.gz
