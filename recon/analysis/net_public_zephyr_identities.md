# CPUNET public Zephyr identity closure

Six configured public owners are relocation-masked byte-exact at the firmware addresses below. Raw `FUN_` identities remain reversible.

| VA | owner | bytes | relocations | callers |
|---|---|---:|---:|---:|
| `0x0102eb2c` | `arch_irq_enable` | 28 | 0 | 7 |
| `0x0102fbac` | `bt_hci_driver_register` | 36 | 1 | 1 |
| `0x0103b304` | `sys_timepoint_calc` | 72 | 1 | 2 |
| `0x0103b34c` | `sys_timepoint_timeout` | 66 | 1 | 2 |
| `0x01039bb0` | `assert_post_action` | 14 | 0 | 101 |
| `0x0103b3a6` | `z_impl_k_timer_stop` | 58 | 4 | 0 |

`z_except_reason` is not a function in this configuration: `assert_post_action` expands it to the exact ARM Mainline `svc #2` sequence. `k_timer_stop` is likewise a generated inline facade for the proven `z_impl_k_timer_stop` section because userspace is off.

The three source units that distinguish the adjacent older family reject their v3.3.99 blobs. The four v3.4.99 patch tags have identical source blobs here, so the OTA manifest—not body overclaiming—pins `v3.4.99-ncs1-1`. SDC remains report-only.
