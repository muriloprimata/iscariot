/* Iscariot: program entry point. No libc, so we write _start ourselves.
 * The program defines: void isc_start(long *sp);
 * sp[0] = argc, sp[1..argc] = argv, then NULL, then envp. */
#ifndef ISC_START_H
#define ISC_START_H

__asm__(
".global _start\n"
"_start:\n"
"xor %ebp, %ebp\n"
"mov %rsp, %rdi\n"
"and $-16, %rsp\n"
"call isc_start\n"
"hlt\n"
);

#endif
