# Crypto and codec stock-version audit

Date: 2026-07-18

This report distinguishes an exact **selected implementation** from an exact
**release label**.  Function bytes can prove the former even when adjacent NCS
releases pin the same module revision and therefore cannot prove the latter.

## libLC3

The west-manifest checkout is stock libLC3 commit
`448f3de31f49a838988a162ef1e23a89ddf2d2ed`.  The configured CPUAPP objects use
GCC 12.2, Cortex-M33 hard float, `-O3`, `-ffast-math`, function sections and
data sections, as required by Zephyr's libLC3 module integration.

All 41 catalogued encoder functions are now configured-object exact after
masking only `R_ARM_ABS32`, `R_ARM_THM_CALL`, and `R_ARM_THM_JUMP24` link
relocations:

- 28 match their complete configured input section;
- 13 match the complete firmware executable extent as a prefix of a section
  whose suffix is alignment, a literal pool, or a trailing table;
- all 90 call relocations inside those extents resolve to the same named
  firmware target.

The audit corrected two formerly plausible but wrong static-helper identities.
Firmware `0x0006aa98` matches `arm_resample_8k_12k8` over all 214 firmware
bytes; the former 48 kHz candidate is a different 420-byte implementation.
Firmware `0x0006bfc8` matches `spectral_shaping` over all 1,940 firmware bytes;
the configured object does not emit a standalone `compute_scale_factors`, and
the caller relocation explicitly names `spectral_shaping`.

The exact machine receipt is
`recon/ownership/app_lc3_stock_atomic_adoption.json`.  NCS 2.5.0, 2.5.1 and
2.6.0 all pin this same libLC3 commit, so these bytes prove the module source
state but cannot distinguish the enclosing NCS patch release.  The exact NCS
2.5.1 label remains west-manifest provenance.

## TinyCrypt

The selected stock revision is
`3e9a49d2672ec01435ffbf0d788db6d95ef28de0`.  Twenty-seven executable owners
across the AES, CMAC, SHA-256, HMAC, HMAC-PRNG and utility translation units are
exact under CPUAPP's `-Os` hard-float build.  Two byte-identical static-helper
ties are resolved by their owning source/caller closure.  The exact inventory
is `recon/analysis/tinycrypt_pinned_matches.json`.

This TinyCrypt revision is shared by the sampled NCS 2.5.0 through 2.6.0
manifests.  It proves TinyCrypt source ownership, not the enclosing NCS patch.
Configured but garbage-collected decrypt/compare functions must remain absent;
their presence in the upstream object is not firmware ownership evidence.

## Mbed TLS and CC312

The manifest's annotated Mbed TLS tag is `v3.3.0-ncs2-1`; it dereferences to
source commit `acea48fc8a5eb227033b55e6ec012731218e257f`.  The local checkout's
later co-located descriptive tag does not imply different source: the selected
headers and library sources have the manifest-tag content.

On nRF5340 CPUAPP, the concrete AES/SHA/entropy/CTR-DRBG implementation closure
is primarily Nordic's hard-float, no-interrupts CC312 platform archive version
0.9.18, not generic upstream Mbed TLS C.  All 89 selected input sections across
31 archive members match the firmware after masking 345 link relocations,
covering 9,564 unmasked bytes with no gap or firmware glue inside the archive
span.  Version 0.9.19 is rejected because five firmware-required selected
sections are absent.  See `recon/catalogs/cc312_archive_ownership.json`.

This authorizes the exact selected archive members.  It does not authorize a
bulk replacement of unrelated Mbed TLS or private CC312 state merely because
the public API names match.

## Oberon and private controller libraries

The sampled nine Oberon P-256 bodies are compatible with both archive versions
3.0.13 and 3.0.14.  Therefore 3.0.13 is the manifest-selected version, not a
body-unique inference.  Per-member ownership remains required.

SoftDevice Controller and MPSL remain report-only.  Their archive-family hashes
are useful version evidence, but private/ambiguous internal symbols are not
automatically removed from the reconstruction.
