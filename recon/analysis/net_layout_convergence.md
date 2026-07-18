# CPUNET layout convergence

The cohesive build now starts from recovered production entrypoint
`FUN_0102a720`, with the public Zephyr `main` symbol assigned directly to the
same address by the linker.  This adds no wrapper instructions.  The recovered
address-taken ESB clock callback `FUN_0102b758` is also an explicit link root,
so its six-function closure survives section garbage collection.  No SDC
section is retained artificially.

## Final production-root measurement

The clean build at runtime base `0x01008800` has zero undefined symbols and
uses 215,293 bytes of FLASH (94.71% of 222 KiB) and 51,416 bytes of RAM (78.45%
of 64 KiB).  The recovered entrypoint and callback closure are live in the ELF:

| Symbol | Runtime address | Size |
| --- | ---: | ---: |
| `main` / `FUN_0102a720` | `0x0102a37c` | `0x408` recovered body |
| `FUN_0102b31c` | `0x0102ab5c` | `0xd4` |
| `FUN_0102b3f0` | `0x0102c908` | `0xe0` |
| `FUN_0102b664` | `0x0102c9e8` | `0xbc` |
| `FUN_0102b718` | `0x0102caa4` | `0x38` |
| `FUN_0102b758` | `0x0102cadc` | `0x40` |
| `FUN_01033858` | `0x0102cb1c` | `0x34` |
| `FUN_010339d0` | `0x0102cb50` | `0x14` |

Current text is `0x31bf8` bytes and ends at `0x0103a4b0`.  Original text ends
at runtime address `0x0103be58`, leaving a `0x19a8` (6,568-byte) pre-data gap.
The fail-closed comparator covers 215,287 file-backed bytes: 5,272 are currently
equal, including 4,677 text bytes.  It reports 19 file-backed sections, zero
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
| text | `0x000b8..0x33658` |
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
