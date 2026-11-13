#!/bin/sh
# Pack rootfs/ plus init and /bin into a gzip'd cpio initramfs.
set -e
cd "$(dirname "$0")/.."
./tools/build-init.sh
./tools/build-cmds.sh
rm -rf out/root
mkdir -p out/root
cp -a rootfs/. out/root/
find out/root -name .gitkeep -delete
mkdir -p out/root/bin
cp out/bin/* out/root/bin/
cp out/init out/root/init
chmod +x out/root/init out/root/bin/*
(cd out/root && find . | cpio -o -H newc 2>/dev/null) | gzip -9 > out/initramfs.cpio.gz
ls -l out/initramfs.cpio.gz
