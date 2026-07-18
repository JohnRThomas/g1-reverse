# CPUNET selected toolchain-member ownership

The fail-closed receipt is
`recon/ownership/net_toolchain_stock_atomic_adoption.json`. It proves five
previously unresolved CPUNET owners directly against the Zephyr SDK 0.16.5-1
no-FP multilib archives and `netcore_image.bin`:

| Analysis VA | Identity | Selected archive member | Exact bytes |
|---|---|---|---:|
| `0x01025d38` | `__udivmoddi4` | GCC 12.2 `libgcc.a(_udivmoddi4.o)` | 668/668 |
| `0x0102a244` | `strcmp` | Picolibc `libc.a(strcmp.S.o)` | 20/20 |
| `0x0103b5c4` | `strnlen` | Picolibc `libc.a(libc_string_strnlen.c.o)` | 24/24 |
| `0x0103b614` | `__aeabi_memcpy4` | Picolibc `libc.a(memcpy.c.o)` | 26/26 |
| `0x0103b62e` | `memset` | Picolibc `libc.a(memset.c.o)` | 16/16 |

All five executable sections have zero relocations, so these are raw byte
comparisons, not mnemonic or relocation-masked similarity. Every catalogued
direct caller site is decoded again by the receipt builder and must resolve to
the claimed analysis-space VA.

`memcpy`, `__aeabi_memcpy`, `__aeabi_memcpy4`, and `__aeabi_memcpy8` are four
symbols on the same 26-byte Picolibc section. The requested readable identity
is `__aeabi_memcpy4`; individual source relocations may legitimately request a
different alias. The section bytes alone cannot distinguish those aliases.

The `libgcc` closure also corrects a catalog boundary. `FUN_0100823c` is the
48-byte `_aeabi_uldivmod.o` section, with relocation-resolved branches to
`__udivmoddi4` and `__aeabi_ldiv0`. The catalogued 50-byte extent incorrectly
absorbed the adjacent two-byte `__aeabi_ldiv0` `bx lr` stub.

Picolibc 1.8.6 and GCC 12.2.0 are configured Zephyr SDK archive provenance.
The exact selected sections prove ownership; they are not claimed to be
patch-unique bodies. This is especially important for short generic libc
routines that can be identical in Newlib or another Picolibc release.

Raw address identities and the existing reconstruction/ownership evidence are
preserved. This receipt authorizes resolving the five missing providers during
the combined naming/manifest generation milestone; it does not delete raw C.
Private SDC and MPSL ownership are outside this receipt and remain unchanged.
