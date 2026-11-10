# Iscariot

A distro for people who hate their own sanity.

## Manifesto

- Iscariot ships only the Linux kernel, an init and a terminal.
- Nothing is installed for you: everything is compiled by you.
- No choice is made for you, not even the libc.
- You are responsible for everything you build.

## Target

- x86_64 (real PC and QEMU)
- Static binaries, no libc
- Build files in C (or HolyC, for those who want to suffer)
- File transfer over the serial port

## Layout

- kernel/    kernel config (tinyconfig)
- init/      PID 1
- libc/      syscall layer, no libc
- shell/     the terminal
- cmds/      basic commands
- build/     build rules
- examples/  example build files
- rootfs/    system root (becomes the initramfs)
- tools/     scripts (packing, running on QEMU)
- out/       build output (bzImage, initramfs)
- docs/      documentation
