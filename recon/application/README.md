# Cohesive dual-core integration builds

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

Override the default `~/ncs251` checkout with `NCS_ROOT`.  Additional arguments
are passed to `west build`; for example, append `-- -Dname=value` for a CMake
cache setting.

The final completion gate is stricter than either shell linking: replace the
temporary `main` roots with the recovered initialization/thread graph, resolve
all duplicate and undefined symbols without weak or multiple-definition
workarounds, then compare the linked `.text`, `.rodata`, and `.data` sections
against both shipped images.
