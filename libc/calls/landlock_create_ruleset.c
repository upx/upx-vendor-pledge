/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2022 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#if HAVE_LANDLOCK /* FIXME: work-around for older glibc/musl */
#include "libc/calls/landlock.h"
/*
#include "libc/intrin/strace.internal.h"

int sys_landlock_create_ruleset(const struct landlock_ruleset_attr *, size_t,
                                uint32_t);
*/

#include <sys/syscall.h>
#include <unistd.h>

/**
 * Create new Landlock filesystem sandboxing ruleset.
 *
 * You may also use this function to query the current ABI version:
 *
 *     landlock_create_ruleset(0, 0, LANDLOCK_CREATE_RULESET_VERSION);
 *
 * @return close exec file descriptor for new ruleset
 * @error ENOSYS if not running Linux 5.13+
 * @error EPERM if pledge() or seccomp bpf shut it down
 * @error EOPNOTSUPP Landlock supported but disabled at boot
 * @error EINVAL unknown flags, or unknown access, or too small size
 * @error E2BIG attr or size inconsistencies
 * @error EFAULT attr or size inconsistencies
 * @error ENOMSG empty landlock_ruleset_attr::handled_access_fs
 */
int landlock_create_ruleset(const struct landlock_ruleset_attr *attr,
                            size_t size, uint32_t flags) {
  int rc;
  rc = syscall(__NR_landlock_create_ruleset, attr, size, flags);
  //KERNTRACE("landlock_create_ruleset(%p, %'zu, %#x) → %d% m", attr, size, flags,
  //          rc);
  return rc;
}
#endif /* HAVE_LANDLOCK */
