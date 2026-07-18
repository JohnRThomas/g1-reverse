# Stock library version and configuration fingerprint

Date: 2026-07-18

The firmware is consistent with stock components, but a release-family or
symbol-name match is not sufficient ownership evidence.  Adoption is performed
per source unit using configured GCC 12.2 objects, relocation-normalized bytes,
CFG/call shape, literal addends, data-layout offsets, and source/archive hashes.

## Exact pins

| Component | Evidence-backed revision |
|---|---|
| NCS/nrf | `87355af5914e498f449b7a68bb5641031a7b8885` |
| Zephyr comparison/source baseline | `83980fe1679441be9b0e1db556a353f6118fe14f` (`v3.4.99-ncs1-1`) |
| liblc3 | `448f3de31f49a838988a162ef1e23a89ddf2d2ed` |
| TinyCrypt | `3e9a49d2672ec01435ffbf0d788db6d95ef28de0` |
| OpenAMP | `42b7c577714b8f22ce82a901e19c1814af4609a8` |
| libmetal | `b91611a6f47dd29fb24c46e5621e797557f80ec6` |
| hal_nordic/nrfx | `9784731461018d3e983604698fbbed6af2bea801` |
| Mbed TLS | `acea48fc8a5eb227033b55e6ec012731218e257f` |
| nrfxlib | `ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7` |
| C library/toolchain | newlib 3.3.0 nano, Zephyr SDK 0.16.5-1, GCC 12.2.0 |

The OTA metadata reports private Zephyr revision
`1b8581519f7aaeef086c6a3d3df59479b2a337d2-dirty`.  That object is not present
in local or public refs.  The exact NCS manifest selects `ncs1-1`; tested source
units match that revision.  `ncs1-2` differs only in an unrelated Wi-Fi shell
unit and cannot be distinguished by the tested firmware units.  `ncs1-3` is a
worse candidate because it changes ATT and `hci_core.c`; the firmware matches
the `ncs1-1` source hashes and configured objects.

## Decisive Bluetooth configuration correction

`CONFIG_TRACING=n` is structurally and instruction-byte exact.  With tracing
disabled, `struct bt_dev` has size `0x170` and these firmware offsets:

- `ncmd_sem = +0x128`
- `sent_cmd = +0x140`
- `cmd_tx_queue = +0x14c`
- `drv = +0x168`

Tracing enabled appends tracking fields to `k_sem` and `k_queue`, shifting the
same fields to incorrect offsets.  Upstream `hci_tx_thread` from Zephyr
`83980fe` matches firmware `FUN_000545f0` over all 348 executable bytes after
relocation normalization, including both inline assert/SVC paths and the
literal addends.  `FUN_0005463e` and `FUN_00054688` are therefore interior
`svc #2` continuations, not functions or missing library owners.

All 33 adopted public Bluetooth owners and all 21 adopted `kernel/work.c`
owners plus four hidden/support bodies remain exact with tracing disabled.
The corrected configured `.config` SHA-256 is
`c0d7ca757a7f944f7c8ed37c98b1c3147d19d16f4f3e7832fcddaf85af49772b`.

## Scope limits

- Exact stock ownership is asserted per source unit, not globally for the
  unavailable private Zephyr commit.
- `log_output.c` is exact stock; configuration/private-state-sensitive
  `log_core.c` residue remains namespaced rather than bulk-adopted.
- Only proven `thread.c` helpers are adopted.  Full init/static-thread machinery
  requires independent root and layout proof.
- Newlib-nano owners are adopted only from exact selected archive members;
  generic fdlibm source similarity is not enough for bulk libm adoption.
- Private SDC remains report-only.  No internal SDC body is removed without a
  unique per-VA archive/member and state-closure proof.

The machine-readable provenance and ownership gates are in
`recon/catalogs/upstream_library_provenance.json` and
`recon/ownership/adoption_manifest.json`.
