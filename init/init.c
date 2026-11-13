/* Iscariot init: PID 1. Must never exit, or the kernel panics. */
#include "isc.h"
#include "start.h"

#define SYS_dup2 33
#define O_RDWR   2

static char *sh_argv[] = { "/bin/sh", 0 };
static char *sh_envp[] = { "PATH=/bin", 0 };

void isc_start(long *sp)
{
long fd, pid;
int status;

(void)sp;
sys_mount("devtmpfs", "/dev", "devtmpfs", 0, 0);

fd = syscall3(SYS_open, "/dev/console", O_RDWR, 0);
if (fd >= 0) {
syscall2(SYS_dup2, fd, 0);
syscall2(SYS_dup2, fd, 1);
syscall2(SYS_dup2, fd, 2);
}

print("\nIscariot\n");
print("Abandon all hope, ye who enter here.\n\n");

for (;;) {
pid = sys_fork();
if (pid == 0) {
sys_execve("/bin/sh", sh_argv, sh_envp);
print("init: cannot run /bin/sh\n");
sys_exit(1);
}
if (pid > 0) {
sys_wait4((int)pid, &status, 0);
if (status != 0) {
print("init: shell failed, halting\n");
for (;;)
sys_pause();
}
} else {
sys_pause();
}
}
}
