# Upstream adoption and build-integration plan

This document defines how the reconstructed app and net images should adopt
the exact upstream NCS 2.5.1 sources and Nordic archives identified by the
ownership catalogs. It is a build plan only: the canonical reconstructed
function bodies remain evidence and must not be deleted or edited as part of
adoption.

## Current build state

The repository does not yet contain a cohesive Zephyr application build.
`recon/west.yml` and `recon/board/prj.conf` exist, but there is no application
or network-core `CMakeLists.txt`/Kconfig source-selection layer.
`tools/full_link.py` is a reconstruction probe: it globs every file under
`recon/symbolized/<core>/`, compiles no Zephyr modules, and links no SDK
archives. Do not turn on upstream libraries in that driver without first
adding the ownership exclusions below, or duplicate definitions will result.

There is also a concrete configuration mismatch in `recon/board/prj.conf`.
It enables `CONFIG_SW_CODEC_LC3_T2_SOFTWARE`, while
`recon/catalogs/lc3_ownership_app.json` identifies the firmware implementation
as the pinned Zephyr `liblc3` source. The final app build must disable the T2
codec selection and use `CONFIG_LIBLC3=y`.

## Pinned inputs

No extra west projects should be added. `recon/west.yml` imports the pinned
NCS manifest, which in turn imports the required projects:

| Component | Revision | Checkout/integration |
|---|---|---|
| NCS | `87355af5914e498f449b7a68bb5641031a7b8885` | `recon/west.yml` |
| Zephyr comparison baseline | `v3.4.99-ncs1-1` / `83980fe1679441be9b0e1db556a353f6118fe14f` | `/Users/freedomcoder/ncs251/zephyr` |
| liblc3 | `448f3de31f49a838988a162ef1e23a89ddf2d2ed` | `/Users/freedomcoder/ncs251/modules/lib/liblc3` |
| TinyCrypt | `3e9a49d2672ec01435ffbf0d788db6d95ef28de0` | `/Users/freedomcoder/ncs251/modules/crypto/tinycrypt` |
| Mbed TLS | `v3.3.0-ncs2-1` (dereferenced commit `acea48fc8a5eb227033b55e6ec012731218e257f`) | `/Users/freedomcoder/ncs251/modules/crypto/mbedtls` |
| nrfxlib | `v2.5.1` (dereferenced commit `ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7`) | `/Users/freedomcoder/ncs251/nrfxlib` |

The OTA manifest records the firmware's Zephyr checkout separately as
`1b8581519f7aaeef086c6a3d3df59479b2a337d2-dirty`.  That object is not
available in the public Nordic `sdk-zephyr` repository.  Therefore the clean
NCS Zephyr pin above is a reproducible comparison baseline, not blanket
source-exact ownership authority.  Continue to prove Zephyr kernel, Bluetooth,
logging, settings, and driver units individually.  Separately versioned west
modules and hash-pinned nrfxlib archives use the identities in
`recon/catalogs/upstream_library_provenance.json`.

Before every reproducible build, verify these revisions with `west manifest
--freeze` and `git rev-parse HEAD`. Also verify the archive SHA-256 values
recorded in the catalogs; do not silently accept a different co-located tag or
archive variant.

Run the repository's read-only preflight before configuring either image:

```text
PYTHONSAFEPATH=1 .venv/bin/python tools/upstream_preflight.py
```

It checks the pinned manifests at their committed revisions, annotated-tag
objects and peeled commits, checkout HEADs, catalog/archive path and SHA-256
agreement, and ELF attributes for the app hard-float CC312 and net soft-float
no-DSP multirole SDC variants. `--json` emits deterministic machine-readable
output for build automation; any failed check produces a nonzero exit status.

## Minimal build shells

Add separate, initially standalone image shells only after the generated
ownership list described below exists:

- `recon/application/app/CMakeLists.txt` and
  `recon/application/app/prj.conf`
- `recon/application/net/CMakeLists.txt` and
  `recon/application/net/prj.conf`

Each CMake file needs only the standard Zephyr preamble and a generated list
of retained reconstruction sources:

```cmake
cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(g1_app) # g1_net for the standalone net image
include(${CMAKE_CURRENT_LIST_DIR}/../../generated/app_retained_sources.cmake)
target_sources(app PRIVATE ${G1_RETAINED_SOURCES})
```

The generated file name is illustrative, but its content must be generated
from the catalogs and address maps, not from filename globbing or a manually
maintained deny-list. Prove the app and net images separately first. After
that, integrate the net configuration through the NCS 2.5.1 HCI-RPMsg child
image (`child_image/hci_rpmsg.conf`) so the normal IPC/shared-memory wiring is
retained.

Do not manually add upstream `.c` files to `target_sources()`. The pinned
Zephyr/NCS module CMake files already select their sources, include paths,
compile options, companion sources, archive variants, and link order.

## App-core selection

### liblc3

Use:

```text
CONFIG_LIBLC3=y
CONFIG_FPU=y
CONFIG_FP_HARDABI=y
# CONFIG_SW_CODEC_LC3_T2_SOFTWARE is not set
```

`/Users/freedomcoder/ncs251/zephyr/modules/liblc3/CMakeLists.txt` compiles the
12 pinned codec source files, including `tables.c`, with `-O3 -std=c11
-ffast-math`. The app architecture contributes `-mcpu=cortex-m33 -mthumb
-mfpu=fpv5-sp-d16 -mfloat-abi=hard`; the build must also retain
`-ffunction-sections -fdata-sections`. The catalog owns 41 firmware functions
and 22 tables. Exclude all of them from the reconstructed source/data inputs
when the upstream module is enabled. Because static helpers are not separable
link inputs, adoption is at upstream object granularity, not individual public
function granularity.

The catalog documents functions whose firmware extent includes trailing data
or whose code size varies. Those entries require semantic/normalized-disasm
comparison and table-byte comparison; raw function-size equality is not a
universal gate.

### TinyCrypt and Zephyr Bluetooth

Use the exact app primitive set recovered from the reference build:

```text
CONFIG_TINYCRYPT=y
CONFIG_TINYCRYPT_AES=y
CONFIG_TINYCRYPT_AES_CMAC=y
CONFIG_TINYCRYPT_SHA256=y
CONFIG_TINYCRYPT_SHA256_HMAC=y
CONFIG_TINYCRYPT_SHA256_HMAC_PRNG=y
CONFIG_BT_HCI_HOST=y
CONFIG_BT_HOST_CRYPTO=y
CONFIG_BT_CRYPTO=y
CONFIG_BT_SMP=y
```

This selects the pinned TinyCrypt `aes_encrypt.c`, `cmac_mode.c`, `sha256.c`,
`hmac.c`, and `hmac_prng.c` objects that own the 18 cataloged app functions.
The Bluetooth settings select the app-host implementations in
`subsys/bluetooth/host/hci_core.c`, `subsys/bluetooth/host/crypto.c`, and
`subsys/bluetooth/crypto/bt_crypto.c`, including the six cataloged functions.
Do not add those source files manually. In particular, `bt_rand` and
`bt_encrypt_le` must resolve to the app-host objects, not same-named controller
implementations.

### CC312

The authoritative ownership input is
`recon/catalogs/cc312_archive_ownership.json`, not only the 32 named entries in
`upstream_crypto_ownership.json`. Relocation-normalized comparison proves the
entire firmware interval `[0x0007954c, 0x0007c00c)`:

- 10,944 bytes;
- 89/89 input sections;
- 31 archive members;
- 9,564 unmasked bytes exact;
- 345 normalized relocations; and
- zero firmware glue or gaps inside the interval.

Therefore the generated adoption manifest must exclude every reconstructed
function/section in that complete interval according to the CC312 catalog. It
must not retain an apparent unnamed function merely because it was absent from
the earlier named subset. The first non-CC312 address is `0x0007c00c`.

Use the normal NCS security selection:

```text
CONFIG_NRF_SECURITY=y
CONFIG_MBEDTLS_LIBRARY_NRF_SECURITY=y
CONFIG_MBEDTLS_PSA_CRYPTO_C=y
CONFIG_PSA_CORE_OBERON=y
CONFIG_PSA_CRYPTO_DRIVER_CC3XX=y
CONFIG_NRF_CC3XX_PLATFORM=y
```

The nrfxlib integration imports this exact archive:

```text
/Users/freedomcoder/ncs251/nrfxlib/crypto/nrf_cc312_platform/lib/
  cortex-m33/hard-float/no-interrupts/libnrf_cc312_platform_0.9.18.a
SHA-256: 80a253291ae78f26b2d38cdccac20c8420f1545b85a476c3029eb92286d9159e
```

`nrfxlib/crypto/CMakeLists.txt` deliberately imports it as the normal static
target `nrf_cc3xx_platform`, not with `--whole-archive`; it also adds the
correct Zephyr abort/mutex companion source and orders newlib after the
archive. Preserve that integration rather than linking the archive path
directly.

## Network-core selection

The network core must remain Cortex-M33 soft-float (`-mcpu=cortex-m33 -mthumb
-mfloat-abi=soft`) and use the normal HCI-RPMsg/SoftDevice Controller settings:

```text
CONFIG_TINYCRYPT=y
CONFIG_TINYCRYPT_AES=y
CONFIG_BT_LL_SOFTDEVICE=y
CONFIG_BT_LL_SOFTDEVICE_BUILD_TYPE_LIB=y
CONFIG_BT_LL_SOFTDEVICE_MULTIROLE=y
CONFIG_BT_CTLR_LE_ENC_SUPPORT=y
CONFIG_BT_CTLR_LE_ENC=y
CONFIG_BT_HCI_RAW=y
CONFIG_IPC_SERVICE=y
CONFIG_IPC_SERVICE_BACKEND_RPMSG=y
CONFIG_MBOX=y
```

These settings cause `nrfxlib/softdevice_controller/CMakeLists.txt` to select:

```text
/Users/freedomcoder/ncs251/nrfxlib/softdevice_controller/lib/
  cortex-m33+nodsp/soft-float/libsoftdevice_controller_multirole.a
SHA-256: f218b3dc4badd8f534f4aa00db678f54a1d4795d7d39721f28401fb49e880e81
```

The archive's private implementation symbols are obfuscated and are not a
license to infer public C prototypes. Initially retain and CFG-verify the two
private SDC candidates listed in `upstream_crypto_ownership.json` until the
final link map and disassembly prove they are subsumed. Always retain the seven
cataloged NRF_CCM integration/glue functions unless the exact archive linkage
proves otherwise. The current name `sdc_llcp_release_rx_context` at
`0x0101fca8` conflicts with its CCM-cluster evidence and must not be treated as
ownership proof.

## Collision and source-ownership rules

Generate an adoption manifest keyed by `(core, firmware VA, raw symbol)`, using
these authorities in order:

1. `recon/catalogs/cc312_archive_ownership.json` for the complete CC312 span;
2. `recon/catalogs/lc3_ownership_app.json` for liblc3 functions and tables;
3. `recon/catalogs/upstream_crypto_ownership.json` for TinyCrypt, Zephyr BT,
   the initial SDC candidates, and retained glue; and
4. the app/net address-name catalogs to map ownership to the current generated
   or symbolized filename.

Then construct each image source list as all canonical reconstructed inputs
minus adopted inputs. Keep the canonical `.c` files on disk as provenance.
Apply these rules:

- exclude source-owned LC3, TinyCrypt, and Zephyr BT definitions before their
  upstream modules are enabled;
- exclude the complete proven CC312 span before enabling its archive;
- exclude an SDC candidate only after the exact final archive composition
  proves that the relevant firmware implementation is supplied;
- retain firmware/integration glue and verify it with `cfg_verify`;
- never resolve collisions using `--allow-multiple-definition`, weak wrappers,
  link-order accidents, or `--whole-archive`; and
- retain a VA back-map for static/private upstream helpers, but do not create
  public aliases solely to expose them.

An archive definition that is not pulled into the final link is not an adopted
implementation. Archive exclusions therefore require a link-map ownership
gate, not just an `nm` inventory of the archive.

## Verification gates

Adoption is complete only when all of the following pass for both images:

1. **Input identity:** west revisions and both archive hashes match the
   catalogs.
2. **Compile profile:** response files or `compile_commands.json` show GCC
   12.2, app hard-float `-Os`, net soft-float `-Os`, and liblc3's additional
   `-O3 -std=c11 -ffast-math` options.
3. **No duplicate ownership:** the intersection of globally defined symbols
   in retained reconstruction objects and selected SDK objects/archives is
   empty before final link.
4. **Map provenance:** every adopted catalog entry resolves to its intended
   upstream object/archive member; no same-named wrong-core Bluetooth symbol
   is selected. All 89 CC312 sections map to the exact archive.
5. **Link closure:** no unexplained application undefined symbols remain;
   remaining undefineds during a partial-link probe must be genuine SDK/libc
   dependencies.
6. **Glue proof:** every retained ownership=`glue` function passes the
   authoritative `tools/cfg_verify.py` coverage and side-effect comparison.
7. **Upstream equivalence:** source-owned functions pass normalized-disassembly
   and semantic checks appropriate to their catalog evidence. CC312 passes the
   existing relocation-normalized 89-section benchmark.
8. **Image comparison:** compare the final section map and `.text`, `.rodata`,
   and `.data`; preserve the existing 100% table/data byte gate and explain all
   codegen-only text differences.

Only after these gates pass independently should the two images be combined
into the final NCS 2.5.1 dual-core build.
