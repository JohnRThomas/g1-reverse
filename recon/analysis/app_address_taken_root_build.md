# CPUAPP address-taken root build impact

A clean normal-GC pair isolates the generated named roots. Both builds use ordinary byte-verified rodata because the added live closure reaches the currently fixed suffix; production admission therefore remains opt-in.

- Emitted roots present: **83/83**
- FLASH/bin delta: **+35536 bytes**
- `.text` delta: **+35424 bytes**
- `.rodata` delta: **+112 bytes**
- Function-symbol entry delta: **+276**
- New unique function names/bytes: **244 / 32558**
- Firmware comparator equal-byte delta: **+2019**
- Undefined symbols: **0**

After the independent DMIC→LC3 direct-edge repair, baseline ordinary `rodata` already spans `0x0007f9d0..0x000a31c0`; the rooted build spans `0x00088430..0x000abc90`. Both overlap the first fixed table at `0x0008b264`. Address-taken roots remain opt-in while final section layout is unresolved. No table address, padding, broad `KEEP`, or function body was changed to hide the collision.
