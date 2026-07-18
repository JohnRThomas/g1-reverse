# CPUAPP normal-GC convergence

The cohesive CPUAPP links with normal Zephyr section GC. Only named binary-derived roots and byte-verified standalone rodata are retained explicitly; the collision-free verified suffix is fixed at original addresses. No numeric function root, code deletion, or SDC adoption is used.

- Named recovered roots present: **19/19**
- Unresolved root candidates: **0**
- Verified data symbols present: **993/993**
- Fixed-address verified suffix: **81 symbols / 15694 bytes**
- Verified payload: **50583 bytes**; ELF symbol storage: **50598 bytes**
- Undefined symbols: **0**

| Section | Retain-all | Normal GC | Delta |
|---|---:|---:|---:|
| `rom_start` | 340 | 340 | +0 |
| `text` | 699348 | 431900 | -267448 |
| `.ARM.exidx` | 8 | 8 | +0 |
| `initlevel` | 384 | 384 | +0 |
| `device_area` | 624 | 624 | +0 |
| `sw_isr_table` | 552 | 552 | +0 |
| `rodata` | 159932 | 77676 | -82256 |
| `datas` | 3582 | 2534 | -1048 |
| `bss` | 16976 | 14518 | -2458 |
| `noinit` | 60461 | 56797 | -3664 |

The shipped pre-init span is 505432 bytes; normal-GC `.text` is -73532 bytes relative to that span. This span includes original literal/data islands, so it is a convergence bound rather than a claim of exact `.text` size.

The binary-derived root graph is complete: every candidate has a named recovered definition and no numeric firmware address is forced at link time.
