/* Iscariot init: PID 1. Must never exit, or the kernel panics. */
#include "isc.h"

#define SYS_dup2 33
#define O_RDWR   2

void init_main(long *sp)
{
(void)sp;

/* The kernel gives us no /dev in an initramfs: mount it ourselves. */
sys_mount("devtmpfs", "/dev", "devtmpfs", 0, 0);

/* Wire stdin/stdout/stderr to the console. */
long fd = syscall3(SYS_open, "/dev/console", O_RDWR, 0);
if (fd >= 0) {
syscall2(SYS_dup2, fd, 0);
syscall2(SYS_dup2, fd, 1);
syscall2(SYS_dup2, fd, 2);
}

print("\nIscariot\n");
print("Abandon all hope, ye who enter here.\n\n");

for (;;)
sys_pause();
}

/* Entry point: no libc means we write _start ourselves.
 * Align the stack to 16 bytes, then call into C. */
__asm__(
".global _start\n"
"_start:\n"
"xor %ebp, %ebp\n"
"mov %rsp, %rdi\n"
"and $-16, %rsp\n"
"call init_main\n"
"hlt\n"
);
