# CPUNET layout convergence

The production-root build now uses the pinned NCS 2.5.1 HCI-RPMsg entrypoint
from `${ZEPHYR_BASE}/samples/bluetooth/hci_rpmsg/src/main.c`.  The previous
local `src/main.c` is intentionally empty and was only suitable for the first
structural-link probe.  Letting section garbage collection start there omitted
the firmware's RPMsg endpoint, TX thread, queues, and synchronization objects.

This root selection is independently present in `netcore_image.bin`: its
payload contains `HCI rpmsg TX`, `HCI rpmsg RX`, `nrf_bt_hci`, `IPC send blocked
1.5 seconds`, `Unable to send, err %d`, `No available command buffers`, and
`Unknown HCI type %u`.  Those strings match the pinned SDK source rather than a
project-local implementation.

## Measured effect

Both measurements use the correct runtime link base `0x01008800` and the same
fail-closed section comparator.

| Metric | Empty probe main | HCI-RPMsg root |
| --- | ---: | ---: |
| FLASH used | 203,752 B | 206,344 B |
| RAM used | 51,008 B | 52,808 B |
| Compared file-backed bytes | 203,746 | 206,342 |
| Equal bytes | 4,600 | 4,679 |
| Loadable file-backed sections | 18 | 19 |
| Exact non-executable sections | 0 | 0 |

The new `k_queue_area` section and the enlarged semaphore/data regions are the
expected consequence of restoring the HCI-RPMsg roots.  The physical build has
no undefined symbols and remains below both FLASH and RAM limits.

The exact-data gate still fails.  The remaining differences begin before
`.rodata` and shift later section addresses through changed reachable code and
object ordering.  There is no evidence for a safe padding-only linker fix:
forcing individual addresses now would conceal missing or differently sized
owners and would need to be undone as those owners converge.  The next safe
step is to restore and validate remaining production roots/configuration, then
re-run section comparison before introducing any explicit ordering fragment.

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

## ESB and nRF-RPC configuration evidence

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

Only 88 bytes of text become reachable from configuration alone.  The two
remaining original log owners, `app_esb` and `timeslot`, are project-local
roots and are still explicitly missing.  Raw disassembly also exposes missing
catalogued caller boundaries: a function at analysis address `0x01035b20`
calls the absent-source `FUN_0102a720`, and a function at `0x0102b718` calls
the recovered `FUN_0102b31c`.  These roots and their stock ESB/nRF-RPC closure,
not report-only SDC `KEEP()` directives, are the next convergence step.

The current machine-readable result is
`recon/analysis/net_binary_section_comparison.json`; executable text remains
diagnostic, while CFG-directed side-effect verification remains authoritative
for reconstructed function semantics.
