# G1 CPUAPP build shell

This is the standalone Zephyr shell for the reconstructed nRF5340 application
core.  It combines the recovered baseline in `../../board/prj.conf` with the
reviewed upstream selections in `prj.conf`.

The C source list is generated at `../../generated/app_retained_sources.cmake`
from `../../ownership/adoption_manifest.json`.  Do not replace it with a glob
or manually remove canonical reconstruction files.  liblc3, TinyCrypt,
Bluetooth host crypto, and CC312 are supplied by their normal pinned NCS 2.5.1
module integrations.  The symbolized sources reuse reviewed helper headers and
`.inc` fragments from `../../app/src`; that directory is include-only and does
not add canonical function bodies to the target.

Recovered read-only tables are admitted through the separate generated list
`../../generated/app_verified_data_sources.cmake`.  Regenerate that list only
with `tools/verify_data.py --cmake-output`: the tool cross-compiles every table
and byte-compares its emitted symbol with `app_update.bin`, so a skipped or
mismatching input cannot silently enter the build.  Original-image RAM and
read-only references are resolved by the generated `g1_app_globals.ld` pins;
these are non-owning `PROVIDE` symbols, not invented storage.
The integration probe retains the verified payloads to expose symbol/content
collisions, but does not claim their final VAs: interleaving them at original
addresses requires the later whole-image section-layout linker script.

`../../wiring/app_objects.c` remains an evidence inventory rather than a build
input.  It contains explicitly unrecovered queue depths and thread arguments;
compiling guessed `K_*_DEFINE` objects would hide those real wiring gaps.

The NCS 2.5.1 Zephyr integration exports liblc3's private `src` directory
globally.  Since that directory also contains a generic `common.h`, it shadows
nRF Security's Oberon `common.h` and breaks PSA private-field access whenever
liblc3 and CC312 are enabled together.  `CMakeLists.txt` removes only that exact
private path from `zephyr_interface` and adds it back privately to `liblc3`.
The public liblc3 include directory remains global, and the pinned SDK checkout
is not modified.

`discovery_callback.c` is the sole retained source that uses GCC's named
register syntax (`register ... asm("r9")`) to preserve an observed ABI register.
Zephyr compiles application sources as strict C99, where `asm` is unavailable,
so CMake enables GNU C99 for that file only.  The canonical proven source is not
rewritten and every other recovered source remains under Zephyr's default
dialect and flags.

This shell defaults to normal Zephyr section garbage collection.  The generated
`app_gc_roots.cmake` adds only the named application/thread candidates proven by
`app_root_inventory.json`; candidates without a named definition remain visible
in the receipt and are not converted to numeric linker roots.  The 993
byte-verified standalone tables are retained by an object-and-section-limited
RODATA `KEEP`, because absolute-address back-maps do not create ELF relocations
that the garbage collector can follow.

The complementary `app_address_taken_roots.cmake` covers function identities
stored in the shipped callback/config tables.  Its generator scans aligned odd
Thumb pointers only outside capped original function intervals, records every
pointer VA and table owner, and emits a root only when a readable symbol has
exactly one retained definition.  Stock aliases, duplicate owners, and unnamed
identities stay explicit in the JSON receipt; no address is passed to the linker.

Retain-all remains available as an ownership diagnostic.  It adds
`--no-gc-sections` and keeps every recovered section visible to undefined-symbol
and duplicate-definition checks; it does not allow multiple definitions,
weaken symbols, or hide unresolved references:

```sh
west build -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=ON
```

Configure a clean build with the pinned NCS v2.5.1 environment through the
repository wrapper (which also supplies Partition Manager's Python imports):

```sh
recon/application/build_cohesive.sh app /private/tmp/g1-cohesive-app
```

The normal-GC shell now compiles, links, and packages without undefined or
duplicate symbols.  It is still a convergence build, not a byte-identical final
image: three runtime thread-entry candidates lack named definitions, and final
whole-image ordering/placement remains outstanding.  Do not hide those gaps
with weak definitions, numeric roots, or `--allow-multiple-definition`.
