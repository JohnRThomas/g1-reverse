# CPUNET current-corpus CFG overlay

This exact-hash layer preserves the frozen 1,090-source sweep and all 33 previously proven link-gap roots (1,123 sources), then adds the catalog-missed `sdc_event_publish` root and the seven recovered ESB production roots.

- Previous covered inventory: **1,123 PASS; 0 unresolved**
- Current covered inventory: **1,131 PASS; 0 unresolved**
- Inventory digest: `22c3671fd7994b424c3692e3b2aad250fe956b5480afebe819dbce337b8775e7`
- New proof: `FUN_0101b4f4` / `sdc_event_publish`, extent `88`, CFG **PASS 5/5**
- Source: `recon/net/src/FUN_0101b4f4.c` (`9aef41538769aca5e3715fd52eee3e80669110008bcf6febeb9a869b69113778`)
- Receipt: `recon/ownership/net_sdc_event_publish_recovery.json` (`6153a508f8e75686af4249d349152a62a6644c6ef3aa0bb85017e31c826b024e`)
- ESB main: `FUN_0102a720` / `g1_cpunet_main`, extent `1000`, CFG **PASS 5/5**, prefix 512 events
- ESB clock/start closure: 6 new PASS roots; `FUN_0102b31c` freshly reverified

## Current verifier tool hashes

- `tools/cfg_verify.py`: `56a51d52bdb25fce73454ff47d836220464518defc66b42c56f965f1eda9b2a7`
- `tools/net_extract.py`: `ec80c6ed622adce759db81b78a874dc70d9338215800e1d25c023ca08403a6d9`
- `tools/net_recon_kit.py`: `9fde04632cdc6ba306352b83a75f3d8fe0ab453da8524fff060d17832aedfef0`
- `tools/parity/emu.py`: `0e2503bbe2c517ee4c397a41ceec4e5e7e6d9e8ff26f5f5ff3257537f8e6ace0`
- `tools/parity/recon.py`: `22c5cc8d8113ac203fb96091fcffa392902dccd22792148958fcba40a4d5bbc2`
