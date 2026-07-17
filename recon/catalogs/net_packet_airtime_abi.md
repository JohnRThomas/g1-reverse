# CPUNET packet-airtime return ABI

`FUN_010109ec` (`controller_packet_airtime_compute`) is a five-argument pure
arithmetic routine with an exact executable extent of `0x540` bytes. Ghidra
labels its result `undefined8` because `r1` is still live at several return
sites. That live value is not part of the callable ABI.

The immutable firmware has exactly three direct calls:

| Caller | Callsite | Post-call use |
| --- | --- | --- |
| `FUN_01011d14` | `0x01011d70` | Uses `r0` for the duration comparison and returns without reading `r1`. |
| `FUN_010122b4` | `0x010122e4` | Discards the result and immediately returns without reading either result register. |
| `FUN_01012438` | `0x0101262c` | Uses `r0`; `0x010125d2` overwrites `r1` before its first possible read. |

The established ABI is therefore a 32-bit `uint32_t` return in `r0`; `r1` is
ordinary caller-clobbered arithmetic residue. The raw/readable backmap is
`controller_packet_airtime_compute` → `FUN_010109ec`.

`tools/test_net_packet_airtime_abi.py` is the fail-closed guard: it scans the
original image for the complete callsite set and performs post-call `r1`
liveness over each caller CFG. A new callsite or any read of `r1` before an
overwrite/return fails the test instead of silently preserving the scalar ABI.
