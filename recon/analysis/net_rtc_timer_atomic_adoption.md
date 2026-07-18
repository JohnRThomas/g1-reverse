# CPUNET Nordic RTC timer atomic adoption

The pinned Zephyr `v3.4.99-ncs1-1` object is relocation-masked byte-exact for the complete `compare_set` call/state closure. The firmware function at `0x010313ec` is **0x124 bytes**, not Ghidra's 0x100-byte declaration; the omitted tail contains live state stores and literal relocations. The old parity candidate also treated the RTC event register at `0x41016504` as permanently unmapped/zero and therefore deleted a live retry arm; the complete stock-section proof supersedes that blind spot.

| function | firmware VA | bytes |
|---|---:|---:|
| `compare_int_lock` | `0x01031248` | 64 |
| `compare_int_unlock` | `0x010312d0` | 76 |
| `z_nrf_rtc_timer_read` | `0x010313a8` | 68 |
| `compare_set` | `0x010313ec` | 292 |
| `rtc_nrf_isr` | `0x010315f0` | 244 |
| `event_clear` | `0x0103a6ae` | 24 |

NCS 2.4 is excluded by the pre-tick/exact-alarm source and control-flow changes. This source unit is unchanged across NCS 2.5.x and 2.6.x, so it does not independently distinguish those tags; the exact v2.5.1 commit remains manifest-pinned.

The exact config is `CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT=1`, `CONFIG_NRF_RTC_TIMER_LOCK_ZERO_LATENCY_IRQS=y`, `CONFIG_SOC_NRF53_RTC_PRETICK=y`, and `CONFIG_TICKLESS_KERNEL=y`. Private SDC ownership is unchanged and remains report-only.
