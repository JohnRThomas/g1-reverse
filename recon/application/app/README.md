# G1 CPUAPP build shell

This is the standalone Zephyr shell for the reconstructed nRF5340 application
core.  It combines the recovered baseline in `../../board/prj.conf` with the
reviewed upstream selections in `prj.conf`.

The C source list is generated at `../../generated/app_retained_sources.cmake`
from `../../ownership/adoption_manifest.json`.  Do not replace it with a glob
or manually remove canonical reconstruction files.  liblc3, TinyCrypt,
Bluetooth host crypto, and CC312 are supplied by their normal pinned NCS 2.5.1
module integrations.

The NCS 2.5.1 Zephyr integration exports liblc3's private `src` directory
globally.  Since that directory also contains a generic `common.h`, it shadows
nRF Security's Oberon `common.h` and breaks PSA private-field access whenever
liblc3 and CC312 are enabled together.  `CMakeLists.txt` removes only that exact
private path from `zephyr_interface` and adds it back privately to `liblc3`.
The public liblc3 include directory remains global, and the pinned SDK checkout
is not modified.

Configure a clean build with the NCS v2.5.1 environment, for example:

```sh
west build -b nrf5340dk_nrf5340_cpuapp \
  /absolute/path/to/recon/application/app
```

The first milestone is configuration and source-ownership validation.  A
successful final link still requires the recovered objects, linker pins, data
inputs, and board overlay to be reconciled; do not work around unresolved or
duplicate symbols with weak definitions or `--allow-multiple-definition`.
