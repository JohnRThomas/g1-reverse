# Function-pointer relocation rebind (CPUAPP + CPUNET)

Make reconstructed function-pointer references (thread entries, callbacks,
handlers) **relocation-correct**, so the cohesive (relocated) build calls the
right functions. Previously every `ADDR_<name>_THUMB` macro expanded to the
**original-image** Thumb-address literal (e.g. `ADDR_display_dispatch_thread_THUMB
= 0x28bed`). Because the cohesive build relocates functions (app `main`
0x16eb8 -> 0x15510; `flash_ops_thread` 0x23480 -> 0x1f470), those pointers named
the wrong code at runtime.

Fix: redefine each function-pointer macro to yield the **linker-resolved** Thumb
address of the target symbol. Only `recon/symbols/g1_{app,net}_symbols.h` were
edited (the function-address section). No `tools/` logic, no `recon/{app,net}/src`
bodies, no linker relaxations, nothing committed.

## Rebind mechanism (why it is conflict-free)

`symbolize.py`'s header generator only emits the literal and reads a stale
scratchpad `symbol_map.json` that no longer exists, so it cannot regenerate
symbol-relative addresses this session. The headers were therefore rewritten
**systematically by a script** (`scratchpad/rebind.py`), not by hand.

The naive `extern <ret> <name>();` + `&<name>` approach is unsafe: the header is
included by the very TU that *defines* the target, and GCC 12 rejects a redeclaration
whose **return type** differs (empty `()` params compose fine, but `void f()` vs
`unsigned f(...)` is a hard error — verified against the pinned toolchain). To be
universally safe regardless of each target's real signature, each macro binds
through a uniquely-named `__asm__`-labelled data alias:

```c
extern const unsigned char __g1_fp_<macroname>[] __asm__("<target_symbol>");
#define ADDR_<macroname>_THUMB (((unsigned long)&__g1_fp_<macroname>) | 1u)
```

The C identifier `__g1_fp_*` never collides with the real definition or any other
declaration, so no return-type/param/object-vs-function conflict is possible; the
`__asm__` label makes the linker resolve the reference to `<target_symbol>`. The
reference emits `R_ARM_ABS32 <target_symbol>` (the linker ORs in the Thumb bit for
a Thumb `STT_FUNC` target; the explicit `| 1u` keeps bit0=1 idempotently, matching
the original odd/Thumb pointer semantics). `(unsigned long)` matches the existing
`((unsigned long)&g_global)` convention already used for data pointers in the
symbolized sources (ILP32, pointer-width). Data macros (RAM globals / kernel
objects, PROVIDE-pinned) were left untouched — 721 `extern volatile` global decls
unchanged.

## Macros rebound per core

| core | function-ptr macros | **rebound** (reloc) | extern aliases added | kept as literal (unresolved) |
|------|:---:|:---:|:---:|:---:|
| app  | 102 | **78** | 78 | 24 |
| net  | 2   | **1**  | 1  | 1  |

Three app macros carried raw `FUN_` names that were reconstructed under a readable
symbol; these were resolved via `recon/catalogs/function_names_app.json` and bound
to the real defined symbol:
`ADDR_FUN_00021da8_THUMB -> &ble_work_thread`,
`ADDR_FUN_00023844_THUMB -> &brightness_level`,
`ADDR_FUN_0002a8d8_THUMB -> &low_speed_peripheral_dispatch_thread`.

Resolution ground truth was the **global** defined-symbol set of the actual
per-core link inputs (`nm` types `T/W/V/D/B/R` over every `.obj`/`.a` that feeds
the app-core link, excluding sibling images mcuboot/hci_rpmsg; and the net image).
Local/`static` symbols were deliberately excluded — an external `&sym` cannot bind
to them in an honest link (see unresolved list).

## Rebuild status (both cores, honest link)

| core | ELF | undefined (`nm -u`) | duplicate global defs | FLASH |
|------|-----|:---:|:---:|-------|
| **app** (core image) | `/private/tmp/g1-ptr-app3/zephyr/zephyr.elf` | **0** | **0** | **626384 / 982528 B = 63.75%** |
| **net** (standalone probe) | `/private/tmp/g1-ptr-net3/zephyr/zephyr.elf` | **0** | **0** | **227961 B / 226 KB = 98.50%** |

App core FLASH rose 62.70% -> 63.75% (baseline literal build vs rebound): the new
`&entry` relocations pull previously-unreferenced reconstructed entry functions
into the live image (with literal macros the archive members were never pulled —
e.g. `spi_master_init`, `panel_on` were absent from the baseline ELF despite
`--no-gc-sections`). Net FLASH/RAM unchanged (its rebound reference sits in a
not-yet-rooted function; see gc note).

## Relocation-correctness proof (concrete nm-vs-disasm)

`spawn_flash_ops_and_brightness_threads` (called from `run_main_dispatch_thread`)
spawns two threads. `nm` on the rebound app ELF:
`flash_ops_thread` @ **0x0001f470**, `brightness_level` @ **0x0001f7f8**
(original-image addresses were 0x23480 / 0x23844).

Constant pool feeding the two `z_impl_k_thread_create` entry args:

```
BASELINE (literal macros)          REBOUND (this change)
  1f384: .word 0x00023481            1fa4c: .word 0x0001f471   = flash_ops_thread(0x1f470)|1
  1f390: .word 0x00023845            1fa58: .word 0x0001f7f9   = brightness_level(0x1f7f8)|1
```

The baseline embeds the **original** 0x23481/0x23845 (which in the relocated image
is unrelated code); the rebound build embeds **0x1f471 / 0x1f7f9** — exactly the
`nm` addresses with the Thumb bit — passed as the entry operand (`ldr rN,[pc]; orr
rN,#1; bl z_impl_k_thread_create`). Second entry confirmed the same way:
`run_main_dispatch_thread.c.obj` now carries `R_ARM_ABS32` relocations to
`process_task_sync_event`, `transport_dispatch_thread`, and `display_dispatch_thread`
(relocated 0x28bec -> **0x24100**).

## gc-retention is now relocation-backed

Object-level, before vs after, for `spawn_flash_ops_and_brightness_threads.c.obj`:

```
BASELINE relocations: (no reloc to the entry functions — entries were bare ints)
  R_ARM_ABS32 g_flash_ops_thread_stack / g_flash_ops_thread / g_brightness_thread ...
REBOUND relocations:
  0x5c R_ARM_ABS32 flash_ops_thread      <- NEW, real reference to the entry
  0x68 R_ARM_ABS32 brightness_level      <- NEW
```

With the literal macros the thread entry was invisible to the linker, so retention
depended entirely on the app build's `--no-gc-sections` (`RETAIN_ALL=ON`) /
`--undefined=` root ledger. The rebind makes each entry a genuine `R_ARM_ABS32`
reference from its spawn site, which `--gc-sections` follows — so thread-entry
retention is now reloc-backed at the object level. The build flag was **not**
changed (per task); note that dropping `--no-gc-sections` wholesale would still
affect other reconstructed functions that are not yet referenced by any reloc, so
this finding is scoped to thread/callback entries, not a blanket gc-safe claim (a
gc-on app build was not run this session).

The net rebind is likewise correct but not yet in the live image:
`FUN_0101132c.c.obj` now carries `R_ARM_ABS32 FUN_01012438` (was an inline
literal). Both are gc'd only because `FUN_0101132c` itself is not reached from the
net roots — the pre-existing ESB/controller-init wiring gap (boot graph N3), not a
rebind defect.

## Names that would not resolve (kept as original literal, reported)

These target no externally-referenceable defined symbol, so `&<name>` cannot bind
in an honest link (no `--allow-multiple-definition`, no weak/numeric root). Each is
left as its original literal — the same value the build already linked with — and
flagged.

**App — 24 total, two categories:**

1. *Unreconstructed app callbacks (7)* — Ghidra-identified function entries used as
   default callbacks into SDK/open-amp/BT APIs, but never reconstructed (no source,
   no readable name, no SDK alias):
   `FUN_0004d058` (rpmsg_virtio_init_vdev default cb), `FUN_0007eb7e`
   (ipc endpoint cb), `FUN_0007f634`, `FUN_00081c8c` (bt_gatt_foreach_attr cb),
   `FUN_00082d6a` (bt_gatt_discover cb), `FUN_000859c2`, `FUN_00085a04`
   (rpmsg_register_endpoint cb). These are genuine reconstruction gaps.

2. *Stock/SDK functions defined `static` (local) in their library (17)* — the
   symbol exists but is not exported, so no external `&` can bind:
   `attr_read_type_cb`, `bound_cb`, `ept_cb`, `gatt_cancel_encode`,
   `gatt_exec_encode`, `gatt_find_info_encode`, `gatt_indicate_rsp`,
   `gatt_prepare_write_encode`, `gatt_read_group_encode`, `gatt_read_type_encode`,
   `gatt_write_ccc_buf`, `gatt_write_encode`, `gen_hash_m`, `read_included_uuid_encode`,
   `smp_handle_reqs`, `hci_tx_thread`, `z_cbprintf_cpy`. (`hci_tx_thread` and
   `smp_handle_reqs` are stock displacements not in the app manifest; the SDK
   provides them as `t`/local. The rest are Zephyr BT/cbprintf statics.)

**Net — 1:** `FUN_010333e4` (used as ESB event-handler callback in `FUN_010333b4`).
This is an **interior address** — 0x10333e4 is offset 0x30 inside `FUN_010333b4`
(entry 0x10333b4, extent 0x22c), not a distinct symbol. No symbol exists there, and
an interior byte-offset into a *recompiled* function is not codegen-stable, so it
cannot be honestly expressed as `&sym`. Kept literal.

## Files changed

- `recon/symbols/g1_app_symbols.h` — function-address section rewritten (78 aliases + 78 rebinds + 24 literals kept).
- `recon/symbols/g1_net_symbols.h` — function-address section rewritten (1 alias + 1 rebind + 1 literal kept).

Nothing else. Generator (`scratchpad/rebind.py`) and originals backed up in the
session scratchpad. No commit.
