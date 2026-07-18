# CPUAPP normal-GC convergence

The cohesive CPUAPP links with normal Zephyr section GC. Only named binary-derived roots and byte-verified standalone rodata are retained explicitly; no numeric root, forced address, code deletion, or SDC adoption is used.

- Named recovered roots present: **16/16**
- Unresolved root candidates: **3** (0x0002692c, 0x00027cfc, 0x00032420)
- Verified rodata symbols present: **993/993**
- Verified payload: **50583 bytes**; ELF symbol storage: **50598 bytes**
- Undefined symbols: **0**

| Section | Retain-all | Normal GC | Delta |
|---|---:|---:|---:|
| `rom_start` | 340 | 340 | +0 |
| `text` | 699348 | 420400 | -278948 |
| `.ARM.exidx` | 8 | 8 | +0 |
| `initlevel` | 384 | 384 | +0 |
| `device_area` | 624 | 624 | +0 |
| `sw_isr_table` | 552 | 552 | +0 |
| `rodata` | 159932 | 93372 | -66560 |
| `datas` | 3582 | 2534 | -1048 |
| `bss` | 16976 | 14518 | -2458 |
| `noinit` | 60461 | 56797 | -3664 |

The shipped pre-init span is 505432 bytes; normal-GC `.text` is -85032 bytes relative to that span. This span includes original literal/data islands, so it is a convergence bound rather than a claim of exact `.text` size.

The root graph remains deliberately partial until the three unmapped candidates gain named, proven definitions. They are not silently retained by address.
