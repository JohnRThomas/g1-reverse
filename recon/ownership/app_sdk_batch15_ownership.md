# CPUAPP SDK residue batch 15 ownership

Seven configured SDK helpers are retained as readable CFG-verified C;
the eighth residue is corrected from the false `strtoll_internal`
identity to the shipped newlib-nano `_strtod_l` call.

| Residue | VA | Bytes | Pinned owner / decision | CFG |
|---|---:|---:|---|---|
| `is_regular_addr_valid` | `0x000839dc` | 34 | `zephyr/drivers/flash/soc_flash_nrf.c:is_regular_addr_valid` | PASS (42) |
| `nvmc_word_write` | `0x00065f04` | 18 | `modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c:nvmc_word_write` | PASS (1) |
| `process_queue` | `0x00082114` | 50 | `zephyr/subsys/bluetooth/host/att.c:process_queue (CONFIG_BT_EATT=n)` | PASS (3) |
| `qspi_deactivate` | `0x00066478` | 28 | `modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c:qspi_deactivate` | PASS (40) |
| `remove_timeout` | `0x00074bbc` | 50 | `zephyr/kernel/timeout.c:remove_timeout` | PASS (2) |
| `sys_slist_find_and_remove` | `0x0008137e` | 54 | `zephyr/include/zephyr/sys/slist.h:sys_slist_find_and_remove` | PASS (5) |
| `sys_slist_find_and_remove_2` | `0x00081de2` | 50 | `zephyr/include/zephyr/sys/slist.h:sys_slist_find_and_remove (discarded result)` | PASS (5) |
| `strtoll_internal` | `0x00077a10` | wrapper | `newlib-nano _strtod_l` | PASS (2) |

The raw target `0x00013f58` parses floating syntax and returns a double;
its entry prefix differs from `lib_a-strtoll.o`. A synthetic strtoll body is forbidden.

Canonical result: **8 residues / 8 prior references**, digest-pinned and CFG-verified.
