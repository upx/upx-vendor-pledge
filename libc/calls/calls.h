#ifndef PLEDGE_LIBC_CALLS_H_
#define PLEDGE_LIBC_CALLS_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

char *commandv(const char *, char *, size_t);
int ioprio_set(int, int, int);
int pledge(const char *, const char *);
int unveil(const char *, const char *);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
