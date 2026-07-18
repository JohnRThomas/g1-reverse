# CPUNET `FUN_010333b4` code-generation receipt

Scope: radio-owner initialization at analysis address `0x010333b4`.

The recovered loops now use explicit advancing source/destination pointers.
The fixed queue-table destination is passed through a compiler barrier so GCC
12.2 retains the compact loop instead of expanding eight stores.  This changes
no firmware-visible read, write, call, or return behavior; raw identity and
symbolized address back-maps remain intact.

## Semantic gates

- `cfg_verify.py net FUN_010333b4`: `PASS`, 8 CFG-directed cases.
- Mutation gate (omit the second word of each paired configuration copy):
  `FAIL`, 7 of 8 cases mismatched.

## Size measurements

All object measurements use the pinned GCC 12.2 `-Os` command.  The production
measurement reuses the exact command from the normal-GC cohesive build's
`compile_commands.json`.

| source form | before | after | delta |
|---|---:|---:|---:|
| canonical numeric-address reconstruction | `0x2e0` (736) | `0x2b8` (696) | -40 B |
| production symbolized reconstruction | `0x2a4` (676) | `0x2a0` (672) | -4 B |

The often-quoted `+136 B` is not a real FLASH overage.  `0x22c` is the CFG code
extent through `0x010335df`; the original function's literal pool immediately
follows at `0x010335e0..0x0103365f`.  The next function begins at
`0x01033660`, so the full original owner interval is `0x2ac` (684 bytes).
The production object was already 8 bytes smaller than that interval and is
now 12 bytes smaller.  Counting the candidate literal pool while excluding the
original literal pool creates the false `+136 B` result.

The normal-GC whole-image measurement was attempted in a clean temporary build
directory, but the concurrently updated shared tree overflowed CPUNET FLASH by
761 bytes before final link.  The scoped production object compiled
successfully, and its exact command-level delta above is independent of that
unrelated whole-tree state.
