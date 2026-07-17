# Upstream crypto ownership

`upstream_crypto_ownership.json` records which recovered crypto-related functions belong to pinned open source, exact Nordic archives, or firmware integration glue. It preserves both the raw `FUN_<address>` identity and the current human-readable symbol.

The authoritative revisions are the NCS 2.5.1 manifest pins: Mbed TLS `v3.3.0-ncs2-1` (annotated-tag object `40fbf201...`) and nrfxlib `v2.5.1` (annotated-tag object `fd77d02e...`). The catalog records the dereferenced/local checkout commits separately and documents clean path-scoped diffs for the crypto sources and archives used here.

## Integration order

1. Build the TinyCrypt and Zephyr Bluetooth entries from the pinned NCS 2.5.1 checkout with the cataloged core profile. App-side `bt_rand` and `bt_encrypt_le` are the host implementations; do not silently select the controller files with the same public names.
2. Link the exact CC312 platform 0.9.18 hard-float/no-interrupts archive for CPUAPP. The nRF5340 reference map selects CC312, not CC310. Its DRBG, entropy, AES/SHA, KMU, and low-level driver entries are SDK-owned archive functions, including private helpers.
3. Link the exact Cortex-M33+nodsp soft-float multirole SoftDevice Controller archive for CPUNET. Its private ELF is obfuscated, so the catalog distinguishes exported API evidence from inferred internal ownership.
4. Keep the net NRF_CCM_NS cluster and any unresolved entropy/random wrappers as reconstructions until the final link proves an archive owns them. Re-audit the current `sdc_llcp_release_rx_context` name at `0x0101fca8`: its location and register context indicate CCM work, not an established LLCP identity.

## Verification boundary

This catalog is an integration and provenance aid. It does not claim source parity, archive identity with the shipped firmware, or CFG verification. Before removing any recovered body, compile or link the selected owner under the recorded ABI, compare it with the firmware, preserve the address back-map, and run the applicable CFG-directed side-effect checks for remaining glue.
