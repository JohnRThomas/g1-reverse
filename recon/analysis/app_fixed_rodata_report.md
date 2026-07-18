# CPUAPP fixed verified-rodata placement

Date: 2026-07-18

## Historical outcome and current gate

An earlier normal-GC cohesive CPUAPP build placed 81 complete verified tables
(15,694 bytes) at their original firmware addresses.  The section comparator
improved from 0 to 81 byte-exact non-executable sections.  Every generated
fixed section is exact; there are no load-range overlaps and no sections beyond
the shipped payload.

| Gate | Normal-GC baseline | Fixed verified tables |
|---|---:|---:|
| Exact non-executable sections | 0 | 81 |
| Exact fixed-table bytes | 0 | 15,694 |
| Comparator equal bytes (all sections) | 11,160 | 25,011 |
| File-backed section overlaps | 0 | 0 |
| Out-of-payload sections | 0 | 0 |
| CPUAPP FLASH | 520,040 B | 603,461 B |
| CPUAPP RAM | 74,989 B | 74,989 B |

The fixed image remains within the 982,528-byte application FLASH region
(61.42% used).  The wrapper build linked with zero undefined symbols and
completed MCUboot signing, `app_update.bin`, DFU zip, and merged-image
packaging.

That receipt remains valid for its recorded ELF, but the placement is no
longer safe as the default after the recovered application closure grew. A
clean roots-OFF build on 2026-07-18 now fails closed with two linker overlaps:

- `.g1_verified_rodata_0008b264` overlaps ordinary `rodata`;
- `.g1_verified_rodata_0009f6c6` overlaps the `datas` load range.

`G1_ENABLE_FIXED_VERIFIED_RODATA` therefore defaults to `OFF`. With fixed
placement disabled, the current multi-image build succeeds, retains the
verified tables as ordinary C/rodata owners, and has no file-backed overlaps or
out-of-range sections. Fixed placement remains an explicit layout experiment;
its selection boundary must be regenerated from the final text/rodata layout
before it can become the default again.

## Selection rule

The generator recompiles every entry in
`recon/generated/app_verified_data_sources.cmake` with the pinned ARM GCC,
extracts the owned symbol bytes, and compares them with the shipped MCUboot
payload.  A C owner is replaced by generated assembly only when all of these
conditions hold:

1. the complete compiler-owned symbol, not a prefix excluding padding, matches;
2. the translation unit owns no additional data symbol;
3. its original VA is at or above `0x0008b168`, the exclusive end of every
   file-backed section in the recorded normal-GC baseline;
4. the table is aligned, lies within the original payload, and overlaps no
   earlier selected table.

The 81 accepted tables span `0x0008b264..0x0009f741`.  The catalog records each
source, address, size, alignment, and SHA-256.  The generated CMake list removes
only those C owners, adds one assembly owner, and gives every table a unique
input/output section at its original VA.  Existing normal garbage collection,
the 19 named roots, and the ordinary verified-rodata retention fragment remain
unchanged.

## Why the remaining tables are not fixed yet

870 complete tables begin below the baseline ROM end and would overlap the
current code, SDK-owned immutable data, initialized-data LMAs, or Zephyr
iterable sections if fixed independently.  Another 42 verified C inputs match
only the documented table prefix rather than their full compiler-owned symbol;
they are deliberately excluded from address replacement.  Moving either group
requires coordinated whole-image text/rodata ordering or a separately proven
split of padding/secondary ownership, not a linker override.

## Reproduction and evidence

Generation:

```sh
cd /tmp
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/build_app_fixed_rodata.py
```

Clean multi-image build and packaging:

```sh
/Users/freedomcoder/Projects/G1disasm2/recon/application/build_cohesive.sh \
  app /private/tmp/g1-cohesive-app-fixed-wrapper
```

Authoritative receipts:

- baseline: `recon/analysis/app_binary_section_comparison.json`
- selection: `recon/catalogs/app_fixed_verified_rodata.json`
- resulting ELF comparison: `recon/analysis/app_fixed_rodata_section_comparison.json`

The clean wrapper ELF SHA-256 is
`6d22cc6d49d50e5174245bd0834759b50c6f4598000e74bbc1c914d40722456b`.

Current safe default reproduction:

```sh
/Users/freedomcoder/Projects/G1disasm2/recon/application/build_cohesive.sh \
  app /tmp/g1-cohesive-app-dmic-edge-default
```
