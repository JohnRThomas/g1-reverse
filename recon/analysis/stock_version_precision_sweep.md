# Stock library version precision sweep

Date: 2026-07-18

This sweep separates seven claims which must not be conflated:

1. **firmware-reported identity**: the revision string embedded in the shipped
   manifest, including its `-dirty` qualification;
2. **public manifest baseline**: the stock revision selected by the public NCS
   release manifest used for configured comparisons;
3. **archive blob identity**: the SHA-256 of one complete prebuilt archive;
4. **selected member/section proof**: exact firmware ownership for the pieces
   actually linked from that archive or source unit;
5. **binary-equivalence family**: all sampled releases carrying identical
   archive bytes or indistinguishable selected bodies;
6. **source-body interval**: the inclusive/exclusive history interval over
   which a matched source body is unchanged; and
7. **configuration/ABI proof**: Kconfig, compiler and multilib choices required
   to reproduce the body.

The firmware is consistent with stock libraries.  Some stock units are
unchanged across several releases, so their precise patch revision cannot be
deduced from machine code alone.  In those cases the manifest supplies the
exact checkout while the bytes prove only the stated family.

## Revision conclusions

| Component | Manifest pin | What firmware evidence proves |
|---|---|---|
| NCS/nrf | `87355af5914e498f449b7a68bb5641031a7b8885` (`v2.5.1`) | CPUAPP/CPUNET composition and exact configured owners select the NCS 2.5 generation; the manifest fixes 2.5.1. |
| Zephyr | Firmware reports unavailable private `1b8581519f7aaeef086c6a3d3df59479b2a337d2-dirty`; public NCS 2.5.1 baseline is `83980fe1679441be9b0e1db556a353f6118fe14f` (`v3.4.99-ncs1-1`) | Exact configured public owners prove extensive body/configuration equivalence to the public baseline, not equality to the unavailable private dirty tree. Many bodies are identical through the 2.5 patch family; changed bodies reject sampled NCS 2.4 and 2.6 families. |
| hal_nordic/nrfx | Public NCS 2.5.1 pin `9784731461018d3e983604698fbbed6af2bea801` | A historical configured-object sweep found QSPI to be the strongest adjacent-revision discriminator. The later fail-closed receipt `app_nrfx_stock_atomic_adoption.json` supersedes the old “PDM-only” status: 31 exact owners are now atomically authorized across QSPI (19), clock (5), NVMC (2), and GPPI (5), with their exact assertion/configuration receipts. This proves those configured source-unit closures, not blanket equivalence of all hal_nordic code. |
| nrfxlib | Public manifest pin `ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7` (`v2.5.1`) | Complete MPSL and multirole-SDC archive hashes are identical only in sampled nrfxlib 2.5.0/2.5.1 and differ in 2.4.2, 2.5.2 and 2.6.0. Selected firmware bodies connect the archive family to the image; the public manifest chooses 2.5.1. SDC remains report-only. |
| OpenAMP | `42b7c577714b8f22ce82a901e19c1814af4609a8` | Exact public owner rejects the 2022.10 line and proves the 2023.04 lineage. Several commits in that lineage have identical matched source, so the patch is manifest-derived. |
| libmetal | `b91611a6f47dd29fb24c46e5621e797557f80ec6` | Matched device/I/O sources are unchanged across sampled releases; exact patch is manifest-derived. |
| liblc3 | `448f3de31f49a838988a162ef1e23a89ddf2d2ed` | This same revision is selected by NCS 2.5.0, 2.5.1, and 2.6.0; LC3 cannot distinguish those NCS releases. |
| TinyCrypt | `3e9a49d2672ec01435ffbf0d788db6d95ef28de0` | The same revision is selected by NCS 2.5.0 through 2.6.0; exact owners prove the module revision but not the enclosing NCS release. |
| zcbor | `67fd8bb88d3136738661fa8bb5f9989103f4599e` | With `ZCBOR_STOP_ON_ERROR`, NCS 2.5.x yields 20 meaningful exact opcode-stream matches versus 15 for NCS 2.6's `d3093b5...`; five bodies uniquely reject 2.6. |
| MCUboot | `edfe1e1465dbc698bf9a195816247913490ab391` (`v1.10.99-ncs1-1` manifest revision) | Nine bootutil bodies are exact, but the relevant source is identical across the sampled 2.5.0, 2.5.1, and 2.6 manifests, so this unit does not identify the patch. |
| Mbed TLS | `acea48fc8a5eb227033b55e6ec012731218e257f` (`v3.3.0-ncs2-1` manifest revision) | Public wrappers and selected archive owners must be proven per member; private CC312 state is not bulk-adopted from a version label. |
| CPUAPP libc/libm | Configured package Zephyr SDK 0.16.5-1, GCC 12.2.0, newlib-nano 3.3.0 | Exact selected members come from `thumb/v8-m.main+fp/hard/libc_nano.a` SHA-256 `c6a3f8bf...` and `libm_nano.a` SHA-256 `9a5f5ed0...`. This is hard-float archive/member proof; the exact SDK packaging suffix remains environment provenance. |
| CPUNET libc | Configured reference uses Zephyr SDK 0.16.5-1 Picolibc 1.8.6 | Exact normalized public bodies and link-map members use `thumb/v8-m.main/nofp/libc.a` SHA-256 `1aab30f2...`. This proves compatibility with those selected Picolibc bodies and the soft-float/no-DSP ABI, not whole-firmware archive identity. CPUAPP's newlib-nano proof must not be generalized to CPUNET. |

## Source-history discrimination

Exact object bytes do not always identify an exact patch tag.  The durable
receipt therefore separates the west-manifest pin from the range of upstream
commits that have an identical owner body:

- zcbor is the strongest discriminator.  The exact
  `zcbor_process_backup` body exists from `e01ea4efa176398ab180230567dadba9df30c011`
  (inclusive) until `c9d2c8d29dff31d52be8157b7156766b968612b2`
  (exclusive).  The manifest pin `67fd8bb88d3136738661fa8bb5f9989103f4599e`
  lies inside this untagged 0.7-era interval; tagged 0.6.0 and 0.8.0+ differ.
  `zcbor_simple_put` alone spans a much wider interval and is not a version
  fingerprint.
- the matched mcumgr owner set rejects Zephyr 3.3 and 3.6+, but overlaps both
  the 3.4.99 and 3.5.99 families.  In particular,
  `smp_process_request_packet` has the current body from commit `5c88d455`,
  while the other matched management/transport bodies have broader ranges.
- `boot_set_next` has its current body from MCUboot commit `4ff95da6f631409e1b3340bb972e91deec0ec924`
  and remains identical across many later NCS tags.  It proves the two-image,
  non-Direct-XIP configuration and flash-area mapping, not the MCUboot patch.
- `lseek` and `stream_flash_init` are unchanged across broad Zephyr release
  ranges and carry essentially no patch-version information.

Consequently, the firmware evidence selects the NCS 2.5 / Zephyr 3.4.99
component family, while exact public `v3.4.99-ncs1-1` is comparison-baseline
provenance. The firmware itself reports a distinct unavailable private dirty
commit. The
scoped owner bodies do not distinguish `ncs1`, `ncs1-1`, `ncs1-2`, and
`ncs1-3`; receipts must not claim otherwise.

Each final owner receipt records five independent fields: manifest commit,
source blob hash, identical-body commit interval, configured section digest,
and the Kconfig/devicetree/Partition-Manager hash.  Whole-object hashes are not
used as version identities because DWARF paths and build metadata perturb them.

Crypto/codec precision:

- TinyCrypt has 27 exact executable matches across six translation units (25
  unique identities; two duplicated bodies require caller context).
- LC3's earlier `match_score=1.0` was semantic/size scoring, not byte proof.
  A subsequent relocation-aware configured-object audit now proves all 41/41
  encoder functions: 28 are full-section exact and 13 have an exact firmware
  executable prefix followed only by object-local alignment/literal/table
  bytes.  Ninety call relocations were checked independently against firmware
  targets.  This stronger audit also corrected two identities:
  `0x0006aa98` is `arm_resample_8k_12k8` (not the 48 kHz variant), and
  `0x0006bfc8` is `spectral_shaping` (not `compute_scale_factors`).  The receipt
  is `recon/ownership/app_lc3_stock_atomic_adoption.json`.
- CC312 is uniquely fingerprinted as 0.9.18: all 89 selected sections match;
  five firmware-required sections are absent from 0.9.19.
- The nine tested Oberon P-256 bodies do not distinguish 3.0.13 from 3.0.14;
  3.0.13 remains a manifest pin, not a body-unique inference.

A 13-commit hal_nordic history sweep compiled 62 configured nrfx objects from
NRFX 2.11 through 3.3. No historical or mixed revision improved on the pinned
commit; QSPI ranked `9784731` first while several smaller units lay on broader
body-equivalence plateaus. That sweep is version-discrimination evidence only.
The subsequent configured closure receipt is the adoption authority: it now
authorizes 31 owners from QSPI, clock, NVMC and GPPI. Any hal_nordic owner not
listed in that receipt remains subject to its own source-unit proof.

## Decisive configuration fingerprints

- `CONFIG_TRACING=n`: gives the exact `bt_dev` size and field offsets.
- `CONFIG_THREAD_LOCAL_STORAGE=n`: makes all 35 audited Bluetooth bodies exact;
  TLS enabled changes `bt_conn_send_cb` to use an inlined TLS accessor while
  firmware calls stock `z_current_get`.
- `CONFIG_ASSERT=y`, assertion level 2: required by exact PDM and several
  Zephyr/nrfx paths.
- `CONFIG_ZCBOR_STOP_ON_ERROR=y`: gives 20 meaningful zcbor matches; the
  default stop-on-error-off build gives only six.  `CONFIG_ZCBOR_ASSERT`
  follows the globally enabled `CONFIG_ASSERT` and is not user-settable.
- `CONFIG_MAIN_STACK_SIZE=16384`, `CONFIG_THREAD_CUSTOM_DATA=y`, and
  `CONFIG_THREAD_LOCAL_STORAGE=n`: make stock `z_cstart` byte-exact 228/228.
  Custom thread data supplies the firmware's `stack_info` offset while TLS-off
  preserves the exact `0xf0` frame size.
- CPUAPP: Cortex-M33 hard-float, `-Os`, newlib-nano.
- CPUNET: Cortex-M33+nodsp soft-float, `-Os`, picolibc.

With tracing and TLS both disabled, the audited stock closure is exact for all
35 Bluetooth bodies and all 25 work-queue owners/support bodies.  Exact
Bluetooth structure and ATT/HCI source hashes are stronger version
discriminators than generic kernel functions which remained unchanged across
multiple NCS tags.

The selected hard-float `libc_nano.a` produces exact representatives at 129
firmware VAs, covering 73 archive members and 21,936 representative section
bytes after masking 621 relocations.  The selected `libm_nano.a` adds 33 exact
sections/9,440 bytes, including the 368-byte `__ieee754_sqrt` body.  Small
wrappers can collide after relocation masking, so their final names still
require caller/refgraph evidence; the large stdio, conversion, allocator, and
fdlibm bodies are decisive archive-family fingerprints.  The 33 libm matches
span 33 archive members and 308 masked relocation sites.  Twelve unique
`libgcc.a` multilib sections add 4,046 exact bytes and reject the soft-float,
no-FP, and base-architecture variants.

The previously suspected `log_core.c` version mismatch was an extent/catalog
artifact: ten configured 2.5-generation bodies are exact after proper true
extent and relocation masking.  The distinct `z_log_msg_finalize` difference
belongs to `log_msg.c` and stays retained; it must not be used to reject the
stock `log_core.c` unit.

The same normalization resolved the last `img_mgmt.c` question.  Under the
firmware-selected two-image, progressive-erase configuration, the private
`img_mgmt_upload` section is 0x240 bytes and matches the firmware entry at
`0x000521fc` on every non-relocation byte.  Its 31 relocation sites account
for the apparent raw-object difference.  The complete live closure of
`img_mgmt.c` is exact, including read-info, erase, upload, reset/response
helpers, active-slot/image accessors, hash search, version wrapper, error
translation, and registration.  The configured object comes from manifest
commit `83980fe1679441be9b0e1db556a353f6118fe14f`
(`v3.4.99-ncs1-1`, NCS 2.5.1); there is no firmware-specific img-mgmt fork.
The source blob `305cad41c4459b1e5fea46b9ce06383a535a20dc` is unchanged in
`-ncs1-1`, `-ncs1-2`, and `-ncs1-3`, so this body proves the NCS 2.5 source
and configuration but does not independently distinguish those patch tags;
the exact `-ncs1-1` choice remains manifest provenance.

## CPUNET private-library boundary

The SDC/MPSL archive hashes are strong stock provenance, but private SDC is
still **report-only**.  The direct SDC benchmark covers 325 firmware functions:
255 have exact normalized-opcode matches (218 unique and 37 ambiguous), while
70 remain approximate.  A monolithic/obfuscated archive does not provide safe
per-function source ownership.  Only the public
`sdc_default_tx_power_set` entry is authorized for replacement.

All CPUNET catalog addresses are analysis-space addresses.  Runtime/link
addresses are exactly `analysis + 0x800`; version comparisons must normalize
this rebase before scoring bytes or references.

## Adoption rule

A stock version label is not permission to delete recovered C.  Replace a
retained owner only when a configured source unit or unique archive member is
exact, its callers/state closure is understood, and the normal link proves the
expected collision delta.  Otherwise keep the decompiled/reconstructed body
and its reversible address map until the cohesive source tree is complete.
