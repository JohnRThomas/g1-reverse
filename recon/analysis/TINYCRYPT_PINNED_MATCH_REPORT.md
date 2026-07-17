# Pinned TinyCrypt match audit

This audit compared the app firmware with TinyCrypt commit
`3e9a49d2672ec01435ffbf0d788db6d95ef28de0` from NCS 2.5.1. It found **27
exact executable matches**. The machine-readable evidence and per-address rank
metrics are in `tinycrypt_pinned_matches.json`.

No canonical reconstruction source or function name was changed by this audit.

## Build reproduced

The seven enabled TinyCrypt source units were rebuilt with Zephyr SDK 0.16.5-1
GCC 12.2.0, `-Os`, Cortex-M33 Thumb, AAPCS, FPv5-SP hard float, function/data
sections, C99, and the remaining firmware flags recorded in the JSON artifact.
The enabled configuration is AES, AES-CMAC, SHA-256, HMAC-SHA256, and
HMAC-PRNG. CBC, CTR, CCM, CTR-PRNG, and ECC are disabled.

The reference application currently selects picolibc while the shipped-firmware
notes identify newlib-nano. This does not alter the matched TinyCrypt executable
bodies; it matters only for compiler-lowered helpers such as `_set`.

## Replacement decision

The following public functions can be supplied directly by the pinned source:

- `tc_aes128_set_encrypt_key`, `tc_aes_encrypt`
- `tc_cmac_erase`, `tc_cmac_init`, `tc_cmac_setup`, `tc_cmac_update`,
  `tc_cmac_final`
- `tc_sha256_init`, `tc_sha256_update`, `tc_sha256_final`
- `tc_hmac_set_key`, `tc_hmac_init`, `tc_hmac_update`, `tc_hmac_final`
- `tc_hmac_prng_init`, `tc_hmac_prng_reseed`, `tc_hmac_prng_generate`
- `_copy`, `_double_byte`

The exact file-static matches should come from compiling their owning pinned
source units, not from standalone reconstructed wrappers: `sub_bytes`,
`add_round_key`, `shift_rows`, `mult_row_column`, `gf_double`, `compress`,
`rekey`, and `update`.

`_set` needs SDK-libc integration or a thin compatibility wrapper: the target
has no independent TinyCrypt `_set` body and reaches a memset-like veneer at
`0x0007fec4`. AES decrypt functions/helpers and `_compare` were present in
configured upstream objects where applicable but are not linked as standalone
target functions; they should remain absent unless a reachable consumer needs
them.

## Exactness and ties

For 24 matches the normalized executable operand stream is a complete exact
match. Three early functions (`0x0004fa34`, `0x0004fadc`, `0x0004fca0`) match
the executable prefix exactly; their ELF `st_size` includes trailing literal
pool/alignment bytes that Ghidra correctly excluded from the firmware function
extent.

The rank score is deliberately broader than executable equality: it also weighs
call-target names, recovered signatures, and literals. Consequently an exact
body can score below 1.0. The JSON records the score, runner-up, and gap for
every address.

Two zero-gap cases are resolved by context:

- `0x0004fa1c` is byte-identical to both `sub_bytes` and `inv_sub_bytes`, but its
  caller is `tc_aes_encrypt`, so the correct identity is `sub_bytes`.
- `0x0007feda` is the identical `add_round_key` static helper emitted by both
  AES source units; the linked caller/source cluster selects `aes_encrypt.c`.

## Integration recommendation

Treat the pinned source files as the naming and implementation authority for
this crypto cluster, while retaining address-to-name back-mapping in the repo's
catalogs. Integrate by source unit so static helpers retain their natural scope,
then run the normal link/address audit. This is stronger evidence than locally
reconstructed C and removes the need to maintain 27 independent function-body
reconstructions.
