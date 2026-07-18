# CPUNET current-corpus CFG overlay

This exact-hash layer preserves the frozen 1,090-source sweep and all 33 previously proven link-gap roots, `sdc_event_publish`, and the seven recovered ESB production roots (1,131 sources). It then adds eleven recovered product callbacks and rebinds six cohesive-only source hashes after fresh default-path CFG verification.

- Previous covered inventory: **1,131 PASS; 0 unresolved**
- Current covered inventory: **1,142 PASS; 0 unresolved**
- Inventory digest: `3c01f787b6baf94d637e82d5b2afda0be4f60a4cb97c9ed515e1ff783cf1a802`
- New proof: `FUN_0101b4f4` / `sdc_event_publish`, extent `88`, CFG **PASS 5/5**
- Source: `recon/net/src/FUN_0101b4f4.c` (`9aef41538769aca5e3715fd52eee3e80669110008bcf6febeb9a869b69113778`)
- Receipt: `recon/ownership/net_sdc_event_publish_recovery.json` (`6153a508f8e75686af4249d349152a62a6644c6ef3aa0bb85017e31c826b024e`)
- ESB main: `FUN_0102a720` / `g1_cpunet_main`, extent `1000`, CFG **PASS 5/5**, prefix 512 events
- ESB clock/start closure: 6 new PASS roots; `FUN_0102b31c` freshly reverified
- Latest callback closure: 11 new PASS roots, 6 changed-source PASS rechecks, 376 checks
- Cohesive integration commit: `c0fe95af`

## Current verifier tool hashes

- `tools/cfg_verify.py`: `b9507f5c35130fccba6be686418b42972285aeb6f83aeb804d9541520aea1b90`
- `tools/net_extract.py`: `ec80c6ed622adce759db81b78a874dc70d9338215800e1d25c023ca08403a6d9`
- `tools/net_recon_kit.py`: `c254d28ebef6bd9a4851ba2c7dfea17333d08bff44b807dae2b1147681f2f1d4`
- `tools/parity/emu.py`: `0e2503bbe2c517ee4c397a41ceec4e5e7e6d9e8ff26f5f5ff3257537f8e6ace0`
- `tools/parity/recon.py`: `22c5cc8d8113ac203fb96091fcffa392902dccd22792148958fcba40a4d5bbc2`
