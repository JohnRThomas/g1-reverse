# Cohesive dual-core integration builds

## G1 application-only source view

`src/` is the readable CPUAPP product-code view.  It excludes functions owned
by the compiler runtime, newlib, Zephyr/NCS, LC3, cJSON, crypto libraries, and
other bundled dependencies.  Its `.c` entries are relative symlinks into the
canonical `recon/named/` recovery corpus, so fixes cannot silently diverge
between two copies.  `application_sources.json` records the address, original
`FUN_*` identity, readable name, inclusion decision, and exclusion evidence for
all 2,115 CPUAPP functions.

The LC3 codec implementation is therefore absent from `src/`, while
`app_codec_lc3_test.c` remains: it is G1 integration code which calls the stock
codec.  Ambiguous unnamed functions remain application candidates until
ownership is proven; the generator never silently discards them as libraries.

Regenerate or verify the view with:

```sh
cd /tmp
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/build_app_source_view.py
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/build_app_source_view.py --check
```

`app/` and `net/` are fail-closed integration probes for the recovered CPUAPP
and CPUNET sources.  They deliberately retain otherwise-unreferenced sections
so duplicate owners and unresolved calls cannot be hidden by section garbage
collection.  They are not yet the final production-rooted firmware projects.

Use the checked-in wrapper for clean builds.  It sets `PYTHONSAFEPATH=1`, loads
the repository virtualenv packages, and exposes the pinned NCS Partition
Manager, Kconfig, and MCUboot Python modules to every child image:

```sh
recon/application/build_cohesive.sh app /private/tmp/g1-cohesive-app
recon/application/build_cohesive.sh net /private/tmp/g1-cohesive-net
```

The default retain-all mode is the ownership audit: it is expected to exceed
CPUNET flash once both the recovered corpus and its selected SDK owners are
present, but it must have no undefined or duplicate symbols.  Use normal
section garbage collection for the physical-image link:

```sh
recon/application/build_cohesive.sh net /private/tmp/g1-cohesive-net-link \
  -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
```

Override the default `~/ncs251` checkout with `NCS_ROOT`.  Additional arguments
are passed to `west build`; for example, append `-- -Dname=value` for a CMake
cache setting.

The final completion gate is stricter than either shell linking: replace the
temporary `main` roots with the recovered initialization/thread graph, resolve
all duplicate and undefined symbols without weak or multiple-definition
workarounds, then compare the linked `.text`, `.rodata`, and `.data` sections
against both shipped images.
