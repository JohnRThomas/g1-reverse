# CPUNET scheduler/queue/heap stock closure

The pinned Zephyr `83980fe` objects built with GCC 12.2/`-Os`, `CONFIG_SPIN_VALIDATE=y`, `CONFIG_SMP=n`, `CONFIG_SCHED_DUMB=y`, and `CONFIG_SYS_HEAP_AUTO=y` reproduce every selected firmware section after masking only relocation words. Every Thumb relocation is also resolved to its exact firmware target.

| source unit | exact live sections |
|---|---:|
| `zephyr/kernel/sched.c` | 37 |
| `zephyr/kernel/queue.c` | 5 |
| `zephyr/kernel/kheap.c` | 4 |
| `zephyr/kernel/mempool.c` | 6 |
| `zephyr/lib/os/heap.c` | 19 |

The default `CONFIG_SYS_HEAP_SMALL_ONLY=y` build was tested and matched zero of the 19 selected heap sections. AUTO preserves the runtime small/big header branch visible in the firmware.

The source history excludes adjacent Zephyr 3.3/3.5 scheduler/kernel families. The 3.4.99-ncs1 patch tags contain identical copies of these sources, so exact `-1` provenance comes from the west manifest rather than an impossible body-only distinction. SDC remains report-only.
