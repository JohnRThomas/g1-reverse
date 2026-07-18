# CPUNET layout convergence

The cohesive build now starts from recovered production entrypoint
`FUN_0102a720`, with the public Zephyr `main` symbol assigned directly to the
same address by the linker.  This adds no wrapper instructions.  The recovered
address-taken ESB clock callback `FUN_0102b758` is also an explicit link root,
so its six-function closure survives section garbage collection.  No SDC
section is retained artificially.

## Final production-root measurement

The clean build at runtime base `0x01008800` has zero undefined symbols and
uses 216,553 bytes of FLASH (95.26% of 222 KiB) and 52,744 bytes of RAM (80.48%
of 64 KiB).  The recovered entrypoint and callback closure are live in the ELF:

| Symbol | Runtime address | Size |
| --- | ---: | ---: |
| `main` / `FUN_0102a720` | `0x0102a500` | `0x408` recovered body |
| `FUN_0102b31c` | `0x0102ace0` | `0xd4` |
| `FUN_0102b3f0` | `0x0102ca8c` | `0xe0` |
| `FUN_0102b664` | `0x0102cb6c` | `0xbc` |
| `FUN_0102b718` | `0x0102cc28` | `0x38` |
| `FUN_0102b758` | `0x0102cc60` | `0x40` |
| `FUN_01033858` | `0x0102cca0` | `0x34` |
| `FUN_010339d0` | `0x0102ccd4` | `0x14` |

Current text is `0x31e0c` bytes and ends at `0x0103a848`.  Original text ends
at runtime address `0x0103be58`, leaving a `0x1610` (5,648-byte) pre-data gap.
The fail-closed comparator covers 216,539 file-backed bytes: 7,742 are currently
equal, including 7,045 text bytes.  It reports 19 file-backed sections, zero
exact sections, and zero exact non-executable sections, so structural placement
passes but the exact-data gate remains open.

The remaining differences shift later section addresses through missing or
differently sized code and object ordering.  There is no evidence for a safe
padding-only linker fix: forcing addresses now would conceal those owners.

In particular, zero exact non-executable sections does **not** yet measure the
contents of like-for-like sections.  The original text reaches analysis address
`0x0103b658` (file offset `0x33658`), whereas every current non-executable
interval starts before that point.  The comparator is therefore still aligning
the current `.ARM.exidx`, iterable areas, `.rodata`, and initialized data with
bytes that are original Thumb text.  Recovered original boundaries are:

| Original area | File offsets |
| --- | --- |
| vectors | `0x00000..0x000b8` |
| early text | `0x000b8..0x00200` |
| firmware-info metadata | `0x00200..0x0023c` |
| resumed text | `0x0023c..0x33658` |
| `.ARM.exidx` | `0x33658..0x33660` |
| init/device/ISR/log iterable areas | `0x33660..0x33904` |
| inferred `.rodata` (including the final runtime-base word) | `0x33904..0x36524` |
| initialized-data payload | `0x36524..0x36f5d` |
| Nordic validation metadata | `0x36f60..0x37160` |

This makes closing the roughly 16 KiB pre-data code/layout gap the prerequisite
for meaningful address-aligned non-executable comparison.  As an independent
content check, searching at the recovered original data boundary finds a
byte-exact `0x218`-byte prefix of the current `datas` section at original file
offset `0x36524`; the current address-aligned score hides that convergence.

## Stock init-root Kconfig closure

The original init table at file offsets `0x33664..0x33734` contains 26
eight-byte records. The prior production build emitted 20. All six absent
records have exact NCS 2.5.1 source owners and can be restored without a
synthetic record or linker `KEEP`:

| Original record | Original function | NCS 2.5.1 owner | Proven selection |
| --- | --- | --- | --- |
| `0x3366c` | `pthread_barrier_pool_init` | `zephyr/lib/posix/barrier.c` | `CONFIG_POSIX_API=y` |
| `0x33674` | `pthread_cond_pool_init` | `zephyr/lib/posix/cond.c` | `CONFIG_POSIX_API=y` |
| `0x3367c` | `pthread_mutex_pool_init` | `zephyr/lib/posix/mutex.c` | `CONFIG_POSIX_API=y` |
| `0x33684` | `posix_thread_pool_init` | `zephyr/lib/posix/pthread.c` | `CONFIG_POSIX_API=y` |
| `0x3369c` | `init_mem_slab_module` | `zephyr/kernel/mem_slab.c` | archive-pulled by real POSIX pool/slab ownership |
| `0x3372c` | `check_ext_api_requests` | `nrf/subsys/fw_info/fw_info.c` | `CONFIG_FW_INFO=y` |

The four original POSIX initializers each traverse five objects. That matches
the NCS 2.5.1 `CONFIG_MAX_PTHREAD_{BARRIER,COND,MUTEX}_COUNT=5` and
`CONFIG_MAX_PTHREAD_COUNT=5` defaults selected by `CONFIG_POSIX_API`. The
firmware-info function references runtime address `0x01008a00`, exactly image
base `0x01008800` plus the stock `CONFIG_FW_INFO_OFFSET=0x200`. These two
independent constants make the selections stronger than a name-only match.

`init_mem_slab_module` has no standalone Kconfig gate: `mem_slab.c` is always
offered to the kernel archive and becomes live only when a real slab owner
references it. In this build the POSIX pool closure provides that ownership,
so no custom static object or forced retention is needed for this record.

The tested batch changes the authoritative session-1 production build as
follows:

| Metric | Before | POSIX + FW info | Delta |
| --- | ---: | ---: | ---: |
| FLASH used | 215,293 B | 216,553 B | +1,260 B |
| RAM used | 51,416 B | 52,744 B | +1,328 B |
| text payload | 203,768 B | 204,300 B | +532 B |
| pre-data text gap | 6,568 B | 5,648 B | -920 B |
| init bytes / records | 160 / 20 | 208 / 26 | +48 / +6 |
| compared equal bytes | 5,272 | 7,742 | +2,470 |
| equal text bytes | 4,677 | 7,045 | +2,368 |
| log bytes / owners | 232 / 29 | 232 / 29 | unchanged |

All six stock symbols and exactly 26 init records are now live. The static
thread iterable remains empty, as expected: its missing timeslot worker is a
custom source owner and is not implied by either safe Kconfig selection.

## Log-owner and configuration evidence

The original log-constant iterable is independently decodable as 32 consecutive
eight-byte `{name pointer, level}` records at file offsets
`0x337ec..0x338ec`.  Relative to the earlier HCI-RPMsg-root build, it contains
eight additional owners: `NRFX_TIMER`, `NRF_RPC`, `NRF_RPC_CBOR`, `NRF_RPC_OS`,
`app_esb`, `esb`, `nrf_rpc_ipc`, and `timeslot`.

Selecting `CONFIG_ESB=y` and `CONFIG_NRF_RPC=y` restores the six stock owners.
ESB must use `CONFIG_ESB_DYNAMIC_INTERRUPTS=y` together with Zephyr's dynamic
direct-interrupt support: the default static-interrupt choice selects
`MPSL_FEM_ONLY`, which is incompatible with the full SDC/MPSL controller that
is simultaneously proven present.  The stock-only configuration changes the
measured build as follows:

| Metric | HCI-RPMsg root | ESB + nRF-RPC selected |
| --- | ---: | ---: |
| text | `0x2f694` | `0x2f6ec` |
| FLASH used | 206,344 B | 206,553 B |
| RAM used | 52,808 B | 53,176 B |
| Compared file-backed bytes | 206,342 | 206,543 |
| Equal bytes | 4,679 | 4,698 |
| Log-constant bytes / owners | 192 / 24 | 240 / 30 |

The final recovered-root build emits 232 log-constant bytes, or 29 owners.  The
original has 32.  The three original-only owner names are `app_esb`,
`hci_rpmsg`, and `timeslot`.  Removing the pinned SDK sample entrypoint exposes
`hci_rpmsg` as a still-missing cohesive owner; the recovered raw production
sources currently emit none of those three `LOG_MODULE_REGISTER` records.
Their proper source/object ownership must be restored rather than synthesizing
records or retaining report-only SDC sections.

The `timeslot` owner is specifically product code, not a log record supplied by
the MPSL archive.  Its original static-thread iterable at file offset
`0x337c0` names `mpsl_nonpreemptible_thread_id`, starts the runtime Thumb entry
`0x0102c011` (analysis entry `0x0102b810`) with a `0x400`-byte stack and
cooperative priority `-16`, and its worker passes runtime Thumb callback
`0x0102c145` (analysis entry `0x0102b944`) to MPSL.  The current configuration
therefore reserves exactly one session with
`CONFIG_MPSL_TIMESLOT_SESSION_COUNT=1`; restoring the owner still requires the
custom worker/callback translation unit and its real static queue/thread
objects.  No stock sample source, synthetic log record, or linker retention
rule is a substitute for that closure.

The current machine-readable result is
`recon/analysis/net_binary_section_comparison.json`; executable byte equality
remains diagnostic, while CFG-directed side-effect verification remains
authoritative for reconstructed function semantics.

## Cohesive product-timeslot owner

The missing custom timeslot ownership unit is now live without section
retention.  Its production build uses the recovered `FUN_0102b810` worker,
`FUN_0102b944` MPSL signal callback, and the recovered `FUN_0102b7d0` /
`FUN_0102b900` state/queue leaves.  `G1_COHESIVE_BUILD` replaces only the
reviewed fixed queue, request, and callback references with relocations; the
canonical fixed-address parity path and every `/*=VA*/` back-map remain.

The object initializers come directly from the original image:

- the normal request is type 1, no-guarantee HFCLK, priority 0, 50,000 us
  distance, and 5,000 us length;
- the earliest request is type 0, no-guarantee HFCLK, priority 0, 5,000 us
  length, and 1,000,000 us timeout;
- the message queue has one-byte messages and four slots;
- `mpsl_nonpreemptible_thread_id` has a `0x400`-byte stack, priority `-16`,
  zero options/delay, and the recovered worker entry;
- `LOG_MODULE_REGISTER(timeslot, 3)` reproduces the original level-3 owner.

A clean normal-GC production build (`G1_INTEGRATION_PROBE_RETAIN_ALL=OFF`)
links with zero undefined symbols.  The recovered four functions, one
44-byte static-thread record, the 52-byte message queue, both 16-byte request
objects, the `0x400`-byte stack, and `log_const_timeslot` are all live.  No
`KEEP`, new `-u` root, padding, or automatic SDC removal was introduced.

Measured result after this closure:

| Metric | Timeslot-owner build |
| --- | ---: |
| FLASH used | 225,877 B / 222 KiB (99.36%) |
| RAM used | 54,028 B / 64 KiB (82.44%) |
| text | `0x341a8` bytes; end `0x0103cbe4` |
| original text-end delta | +`0xd8c` (3,468-byte overshoot) |
| log bytes / owners | 256 / 32 |
| compared / equal bytes | 225,602 / 8,566 |
| equal text bytes | 7,199 |

This table is the last successful production measurement before the complete
product-endpoint closure was made live.  That closure restores the `app_esb`
and `hci_rpmsg` owners, so the intended owner set is all 32 original names.

The fail-closed normal-GC integration probe at
`/private/tmp/g1-product-owners-final-v6` compiles the complete endpoint and
timeslot ownership set and reports no undefined-symbol diagnostics, but it
does not produce a final ELF: the load image overflows the 222 KiB FLASH region
by 761 bytes.  Relative to the preceding near-fitting endpoint probe, the
reviewed stock API resolutions add 332 text bytes and 132 rodata bytes (plus
alignment).  No proven root was removed, no hardware region was enlarged, and
no padding, `KEEP`, new `-u`, or automatic report-only SDC removal was used to
hide this result.  Consequently the machine-readable comparator remains the
last successful timeslot-owner measurement; it is not presented as a final
measurement of the now-live endpoint closure.  Code-size/layout reconciliation
is the remaining gate before a fresh comparator can be authoritative.
