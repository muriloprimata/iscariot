/* Iscariot: the smallest possible "libc". Header only. */
#ifndef ISC_H
#define ISC_H

#include "syscall.h"

#define ISC_REBOOT_MAGIC1   0xfee1dead
#define ISC_REBOOT_MAGIC2   672274793
#define ISC_REBOOT_RESTART  0x01234567
#define ISC_REBOOT_POWEROFF 0x4321fedc

static inline long sys_read(int fd, void *buf, unsigned long len)
{ return syscall3(SYS_read, fd, buf, len); }

static inline long sys_write(int fd, const void *buf, unsigned long len)
{ return syscall3(SYS_write, fd, buf, len); }

static inline void sys_exit(int code)
{ syscall1(SYS_exit, code); for (;;) ; }

static inline long sys_pause(void)
{ return syscall0(SYS_pause); }

static inline long sys_fork(void)
{ return syscall0(SYS_fork); }

static inline long sys_execve(const char *path, char *const argv[], char *const envp[])
{ return syscall3(SYS_execve, path, argv, envp); }

static inline long sys_wait4(int pid, int *status, int options)
{ return syscall4(SYS_wait4, pid, status, options, 0); }

static inline long sys_mount(const char *src, const char *dst, const char *type,
                             unsigned long flags, const void *data)
{ return syscall5(SYS_mount, (long)src, (long)dst, (long)type, (long)flags, (long)data); }

static inline long sys_reboot(int cmd)
{ return syscall4(SYS_reboot, ISC_REBOOT_MAGIC1, ISC_REBOOT_MAGIC2, cmd, 0); }

static inline unsigned long isc_strlen(const char *s)
{
unsigned long n = 0;
while (s[n]) n++;
return n;
}

static inline void print(const char *s)
{ sys_write(1, s, isc_strlen(s)); }

#endif
