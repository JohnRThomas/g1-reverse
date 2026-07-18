# CPUNET runtime stock identity resolution

The two reported cohesive-link anomalies are four ordinary stock owners once
CPUNET's address spaces and true section boundaries are applied.  The image is
imported at analysis base `0x01008000`, while absolute flash literals encode
runtime addresses from `0x01008800`; runtime pointers therefore map back to
the analyzed image by subtracting `0x800`.

| Firmware VA | Exact owner | Upstream unit | True extent |
|---|---|---|---|
| `0x0102d25c` | `arch_busy_wait` | Zephyr `soc/arm/nordic_nrf/nrf53/soc.c` | 16 bytes code + 4-byte literal |
| `0x0103b0e8` | `z_impl_k_busy_wait` | Zephyr `kernel/busy_wait.c` | 8 bytes code |
| `0x0102fa84` | `__chk_fail` | Zephyr Picolibc `libc-hooks.c` | 20 bytes code + 4-byte literal |
| `0x0103b53a` | `__memcpy_chk` | Picolibc `libc_ssp_memcpy_chk.c.o` | 38 bytes code |

For `arch_busy_wait`, the literal stored at `0x0102d26c` is runtime address
`0x0103c8a0`.  Its analysis target is `0x0103c0a0`, containing the aligned
six-byte `nrfx_coredep_delay_us` table `03 38 fd d8 70 47`: `SUBS r0,#3`,
`BHI` to itself, `BX lr`.  Reading the runtime value as an analysis address
incorrectly lands on an unrelated IPC string.

For `__chk_fail`, the literal stored at `0x0102fa98` is runtime address
`0x0103dd15`.  Its analysis target `0x0103d515` contains
`* buffer overflow detected *\n`.  After `printk`, the function executes the
exact ARMv8-M Zephyr `ARCH_EXCEPT(K_ERR_STACK_CHK_FAIL)` sequence: clear
`BASEPRI`, load reason 2 into `r0`, then `svc #2`.  The SVC is the terminal
instruction of a real callable `__chk_fail`; it is not a separate function or
an unrepresentable continuation.

The configured objects and Picolibc archive member match every non-relocation
byte.  Firmware branch targets close the call graph as
`z_impl_k_busy_wait -> arch_busy_wait` and
`__memcpy_chk -> {__chk_fail, memcpy}`.  The two existing reconstructed
callers pass authoritative CFG verification (`2` and `0` directed cases,
respectively).  The machine receipt is
`recon/ownership/net_runtime_stock_atomic_adoption.json`; all raw
`FUN_...` address back-maps are preserved.  No SDC/MPSL decision changes.
