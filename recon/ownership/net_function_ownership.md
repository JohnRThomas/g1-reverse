# Net-core function ownership audit

This ledger classifies the 451 entries reported as `missing_genuine_c` by the 2026-07-11 corpus audit. That audit label is an entry-point/catalog classification, not an ownership conclusion.

## Result

All **451/451** entries are owned by the NCS 2.5.1 / Zephyr / Nordic net-core SDK stack. There are **zero newly discovered product-owned net-core functions requiring readable C**, so no reconstruction tasks were spawned.

- 435 entries have ordered Thumb-opcode matches at ratio 0.90–1.00 against `/Users/freedomcoder/ncs251/netref_build`; the JSON records the matched symbol, ratio, and linker-map archive/object provenance.
- `0x0101fdd0` matches an obfuscated SoftDevice Controller routine at 0.917 when allowing the expected 11-op build/config length delta.
- The remaining 15 entries are pinned to Zephyr/Nordic subsystems by embedded source paths plus call-graph locality. (Several addresses contain more than one source-path clue.)

## Ownership boundary evidence

The unmatched tail names upstream paths including `zephyr/lib/posix`, `zephyr/subsys/logging`, `zephyr/drivers/entropy`, `nrf/subsys/bluetooth/controller/hci_driver.c`, `nrf/subsys/mpsl/init`, `nrfx_clock_mpsl.c`, Zephyr kernel sources, and `nrfx_gppi_dppi.c`. Zero-direct-caller routines are reached from SDK init/device tables rather than product C. The matched bulk comes primarily from the obfuscated Nordic SoftDevice Controller archive and normal Zephyr/NCS objects.

The machine-readable ledger is authoritative for per-address evidence and confidence: `recon/ownership/net_function_ownership.json`.
