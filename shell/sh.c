/* Iscariot sh: a tiny shell. Reads a line, runs a program. */
#include "isc.h"
#include "start.h"

#define SYS_chdir 80
#define MAXARGS   16
#define LINEMAX   256

static char line[LINEMAX];
static char path[LINEMAX + 8];
static char *argv[MAXARGS + 1];
static char *envp[] = { "PATH=/bin", 0 };

static int streq(const char *a, const char *b)
{
while (*a && *a == *b) {
a++;
b++;
}
return *a == *b;
}

/* Read one line from the console into line[]. Returns -1 on EOF. */
static long readline(void)
{
long n = 0;
char c;

for (;;) {
if (sys_read(0, &c, 1) <= 0)
return -1;
if (c == '\n' || c == '\r')
break;
if (n < LINEMAX - 1)
line[n++] = c;
}
line[n] = 0;
return n;
}

/* Split line[] in place into argv[]. Returns argc. */
static int split(void)
{
int argc = 0;
char *p = line;

while (*p) {
while (*p == ' ' || *p == '\t')
*p++ = 0;
if (!*p)
break;
if (argc < MAXARGS)
argv[argc++] = p;
while (*p && *p != ' ' && *p != '\t')
p++;
}
argv[argc] = 0;
return argc;
}

static void builtin_echo(int argc)
{
int i;

for (i = 1; i < argc; i++) {
if (i > 1)
print(" ");
print(argv[i]);
}
print("\n");
}

static void run(int argc)
{
const char *cmd = argv[0];
const char *p;
unsigned long n = 0;
int slash = 0;
long pid;
int status;

if (streq(cmd, "help")) {
print("builtins: help cd echo reboot poweroff\n");
return;
}
if (streq(cmd, "cd")) {
if (syscall1(SYS_chdir, argc > 1 ? argv[1] : "/") < 0)
print("cd: no such directory\n");
return;
}
if (streq(cmd, "echo")) {
builtin_echo(argc);
return;
}
if (streq(cmd, "reboot")) {
sys_reboot(ISC_REBOOT_RESTART);
return;
}
if (streq(cmd, "poweroff")) {
sys_reboot(ISC_REBOOT_POWEROFF);
return;
}

/* Not a builtin: run it. No slash in the name means look in /bin. */
for (p = cmd; *p; p++)
if (*p == '/')
slash = 1;
if (!slash) {
const char *b = "/bin/";

while (*b)
path[n++] = *b++;
}
for (p = cmd; *p && n < sizeof(path) - 1; p++)
path[n++] = *p;
path[n] = 0;

pid = sys_fork();
if (pid == 0) {
sys_execve(path, argv, envp);
print("sh: command not found: ");
print(cmd);
print("\n");
sys_exit(127);
}
if (pid > 0)
sys_wait4((int)pid, &status, 0);
}

void isc_start(long *sp)
{
int argc;

(void)sp;
for (;;) {
print("iscariot# ");
if (readline() < 0)
for (;;)
sys_pause();
argc = split();
if (argc > 0)
run(argc);
}
}
