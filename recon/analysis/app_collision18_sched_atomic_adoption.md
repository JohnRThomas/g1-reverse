# COLLISION-18 scheduler atomic adoption

The firmware-configured Zephyr `kernel/sched.c` object is the exact owner of `z_reschedule`, `z_thread_priority_set`, `z_unpend_first_thread`, and `z_thread_abort`. Each selected ELF section matches the firmware's true reachable code extent after masking relocations; the remaining section bytes are literal-pool tails, not executable extent.

The four owners are adopted as one source-unit closure. The fresh normal-link collision set moves **80 -> 76**, removing exactly those four symbols, adding none. The unresolved set stays exactly `FUN_0005463e` and `FUN_00054688`.

Scheduler state references converge on Zephyr's `_kernel` and `sched_spinlock`; the distinct object at `0x2000b470` remains `mutex_spinlock_b470`. Address provenance comments remain in the symbolized sources. SDC ownership remains report-only and unchanged.
