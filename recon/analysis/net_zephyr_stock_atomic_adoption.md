# CPUNET exact Zephyr source closures

The corrected stock build at Zephyr commit `83980fe` uses `CONFIG_SPIN_VALIDATE=y` and `CONFIG_SMP=n`. All 84 live sections from the nine units below are relocation-masked byte-exact, and every Thumb call target is checked against the firmware.

| unit | live functions | private state |
|---|---:|---:|
| `zephyr/lib/os/mpsc_pbuf.c` | 13 | 0 |
| `zephyr/subsys/logging/log_core.c` | 28 | 0 |
| `zephyr/arch/arm/core/aarch32/cpu_idle.S` | 3 | 0 |
| `zephyr/lib/os/onoff.c` | 7 | 0 |
| `zephyr/subsys/net/buf_simple.c` | 6 | 0 |
| `zephyr/kernel/msg_q.c` | 4 | 0 |
| `zephyr/kernel/work.c` | 10 | 2 |
| `zephyr/kernel/timer.c` | 4 | 1 |
| `zephyr/kernel/poll.c` | 9 | 2 |

The ambiguous body at `0x0103a478` is `net_buf_simple_add_mem`: its relocated branch targets `net_buf_simple_add@0x01030084`, not the push owner. SDC ownership remains report-only.
