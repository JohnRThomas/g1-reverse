# Vendor firmware is omitted from this repository

This project analyses the firmware of the Even Realities G1. The **analysis is
published here in full**; the vendor's firmware itself is not.

Removed from the entire history:

| Path | What it was |
|---|---|
| `app_update.bin` | stock app-core image |
| `net_core_app_update.bin`, `netcore_image.bin` | stock network-core image |
| `app_update.bin.{i64,id0,id1,nam,til}` | IDA databases — these embed the loaded program bytes |
| `app_update.bin_2025*.i64` | earlier IDA snapshots, same reason |
| `net_core_app_update.bin.i64` | same |
| `ghidra/EvenDecomp.rep/` | Ghidra project database, same reason |
| `recon/diagnostics/.../app_update_qspi_exporter.signed.bin` | stock image, patched |

Redistributing a vendor's complete copyrighted binary is a different act from
publishing an analysis of it. Disassembly listings, decompiled C, symbol
recovery, structure definitions, test vectors and the evidence excerpts in
`recon/` are our own work and are all here.

## Working with this repository

You need to supply the firmware yourself, from a device you own. Both images can
be read off real glasses with the tooling in the companion repository
(`companion/g1_glasses_ota/`, phase `dump-mem`), or taken from an official
update package.

Drop them at the repository root as `app_update.bin` and
`net_core_app_update.bin`, then rebuild the databases with the scripts under
`recon/`. Addresses throughout the documentation assume the images this project
was developed against — check `docs/` for the expected hashes before trusting a
cross-reference.
