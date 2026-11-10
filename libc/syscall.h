/* Iscariot: raw x86_64 Linux syscalls. No libc, no dependencies. */
#ifndef ISC_SYSCALL_H
#define ISC_SYSCALL_H

#define SYS_read    0
#define SYS_write   1
#define SYS_open    2
#define SYS_close   3
#define SYS_pause   34
#define SYS_getpid  39
#define SYS_fork    57
#define SYS_execve  59
#define SYS_exit    60
#define SYS_wait4   61
#define SYS_mount   165
#define SYS_reboot  169

static inline long syscall5(long n, long a, long b, long c, long d, long e)
{
long ret;
register long r10 __asm__("r10") = d;
register long r8  __asm__("r8")  = e;
__asm__ volatile ("syscall"
: "=a"(ret)
: "a"(n), "D"(a), "S"(b), "d"(c), "r"(r10), "r"(r8)
: "rcx", "r11", "memory");
return ret;
}

#define syscall0(n)            syscall5(n, 0, 0, 0, 0, 0)
#define syscall1(n, a)         syscall5(n, (long)(a), 0, 0, 0, 0)
#define syscall2(n, a, b)      syscall5(n, (long)(a), (long)(b), 0, 0, 0)
#define syscall3(n, a, b, c)   syscall5(n, (long)(a), (long)(b), (long)(c), 0, 0)
#define syscall4(n, a, b, c, d) syscall5(n, (long)(a), (long)(b), (long)(c), (long)(d), 0)

#endif
