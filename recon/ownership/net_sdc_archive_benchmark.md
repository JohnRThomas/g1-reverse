# NCS 2.5.1 SoftDevice Controller archive benchmark

Date: 2026-07-17

This is an archive-specific supplement to `net_function_ownership.json`.  The
older ledger classifies only the 451 entries selected by the corpus audit and
uses the whole `netref_build` as its signature corpus.  It therefore cannot by
itself distinguish SoftDevice Controller code from Zephyr, MPSL, OpenAMP, or
net application glue.

## Exact input and identity

- NCS/nrfxlib revision: `v2.5.1` (`ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7`)
- Archive: `nrfxlib/softdevice_controller/lib/cortex-m33+nodsp/soft-float/libsoftdevice_controller_multirole.a`
- SHA-256: `f218b3dc4badd8f534f4aa00db678f54a1d4795d7d39721f28401fb49e880e81`
- Member: `libsoftdevice_controller_s140_debug_soft__obfuscated.elf`
- ABI: ARM EABI v5, Cortex-M33+nodsp, soft-float.  Candidate identities are
  archive/member/ELF-section/symbol tuples; the section index is required
  because this obfuscated member repeats some local symbol names and bodies.

The benchmark indexed 1,609 member functions having at least 16 bytes and six
decoded Thumb operations.  Firmware functions were compared by ordered,
normalized Thumb mnemonic sequence, with the same length window (+/-2
operations) and 0.90 threshold used by the existing ownership audit.  “Exact”
below means an exact normalized opcode sequence, not byte identity (linked
relocations necessarily differ from the relocatable member).
The previously reviewed `0x0101fdd0` configuration variant is the sole explicit
exception: its established +/-11-operation comparison was repeated directly
against the archive member and retained because its 0.917 best match is unique
by a 0.551 margin.

## Result

| Firmware category | Functions | Catalog bytes |
|---|---:|---:|
| Controller archive, exact unique identity | 218 | |
| Controller archive, exact duplicate/ambiguous identity | 37 | |
| Controller archive, high-confidence approximate unique identity | 64 | |
| Controller archive, high-confidence approximate ambiguous identity | 6 | |
| **Controller archive total** | **325** | **29,028** |
| Other NCS/Zephyr reference objects (not this archive) | 115 | 10,192 |
| Eligible functions uncovered by either upstream corpus | 585 | 106,500 |
| Too small/thunk/too few operations for sound signature ownership | 222 | 1,719 |
| **Firmware catalog total** | **1,247** | **147,439** |

Thus 282 firmware functions have a unique archive symbol identity and 43 have
certain archive-family ownership but ambiguous symbol identity.  The archive
contains 88 duplicate exact-signature groups (260 function identities; largest
group 21), so choosing the first obfuscated symbol for those 43 firmware
functions would be unjustified.  Approximate unique matches all had a
best-versus-runner-up margin of at least 0.03.

The union check against `tools/net_sigmatch.py` is internally consistent: 323
archive hits are also among its 438 whole-reference hits, 115 whole-reference
hits come from other SDK objects, and two additional archive functions are
recovered only by direct archive matching.  The remaining 585 functions are the current
eligible glue/reconstruction population; “uncovered” does not prove product
ownership without a separate source/call-graph audit.

## Information added beyond `net_function_ownership.json`

- 322/325 archive hits occur in the older 451-entry ledger.  Only 232 of those
  carry explicit archive/member provenance there; direct member matching
  qualifies another 89 entries previously recorded only as “NCS 2.5.1 netref
  object index”.  It also pins the ledger's special wider-tolerance
  `0x0101fdd0` match to member section 3530,
  `sym_5I5MTMPTF2F4WI7MIXG5OG4TUPLUR53CB2QHVUA` (61 versus 72 operations,
  ratio 0.917, next candidate 0.366).
- Three archive-owned firmware functions were outside that ledger:
  - `0x010091cc` ->
    `libsoftdevice_controller_multirole.a(libsoftdevice_controller_s140_debug_soft__obfuscated.elf):sdc_default_tx_power_set`,
    ratio 0.900, unique.
  - `0x0100a760` -> same member:
    `sym_HASNIMATEUBBHQBEP2CV75LIZW72YGIFHJCUPHI`, ratio 0.923, unique.
  - `0x0100ec88` -> same member:
    `sym_XOOTGCSEAKA3PUKZW3QYB4DCVC2FKUP2TS5AZ5Q`, ratio 0.988, unique.

## ABI defect exposed by the upstream identity

NCS 2.5.1 declares:

```c
int32_t sdc_default_tx_power_set(int8_t requested_power_level);
```

Firmware caller `FUN_01031a68` loads `r0 = 3` before calling `0x010091cc`, and
the original/archive implementation preserves and forwards that `r0` to its
internal setter.  The current reconstruction instead defines
`unsigned int FUN_010091cc(void)` and calls `FUN_0101e94c()` without an
argument.  It passes the present parity harness only because the compiled
no-argument wrapper happens to leave incoming `r0` live until the nested call.
This is accidental register retention, not the recovered ABI.  The canonical
function was not changed by this benchmark; it should be repaired separately
to an `int32_t (int8_t)` wrapper and verified with a call-argument-sensitive
negative control.
