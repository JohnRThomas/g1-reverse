# CPUNET CFG recheck overlay

This exact-hash overlay preserves the frozen 1,090-source baseline, then closes every non-PASS identity with a current authoritative recheck or its catalog-missed dedicated proof receipt.

- Execution HEAD: `373b844b31dce52edb9c9bfffee8200822c75b0e`
- Current source inventory digest: `c9af933cf0686249bd28cffa3176b87d040a5368d9795a9b962a638747a0978a`
- Aggregate: **1,090 PASS; 0 unresolved**

## Former FAIL

- `FUN_01008d00` — PASS, source `570ed51e6a48ea1db5bbe988dde3d12c0799894fda61e29e37faafeeea7e9f02`
- `FUN_01009bc4` — PASS, source `ac1e46df77b542bd94ca835264993969c9b5403b4efc282a8d437b0c2d4181bf`
- `FUN_01009c68` — PASS, source `db7a5a269574540131b9ac0c850f4251f99ca1c2a4894612323c7b0f52af7556`
- `FUN_0101ab20` — PASS, source `b6e95fa4b284c754e3c0327490542a2522e2d15b11ca7055ff014e22bcbb282c`
- `FUN_010313ec` — PASS, source `604e7914b0d31c10cd0be2ad09f2673a5c3f955ee3526973635b02120142e947`
- `FUN_01033888` — PASS, source `b60bd5d9182914fb56b37f8302c24b669c52dd83ac213f88afbc598e3665b23e`
- `FUN_01033b18` — PASS, source `25a90642d480097ce0746918b8455cdfc0d2783d462c77a3b86f9e3bb963cd2a`
- `FUN_0103499c` — PASS, source `63b09e427d47bab0a2062d172004eb74b5f2d68b955764a919dc68d57a86d2e0`

## Former timeout

- `FUN_010089f8` — PASS within a 300-second bound, source `f2ab92f927685068bfead047c3e357467d1060bc9737712a48b03b75acf0a7d7`

## Catalog-missed dedicated proofs

- `FUN_0100ef08` — PASS (40 checks), `recon/ownership/net_private_shard8_recovery.json`
- `FUN_01011664` — PASS (80 checks), `recon/ownership/net_private_7_recovery.json`
- `FUN_01014b18` — PASS (121 checks), `recon/ownership/net_private_shard1.json`
- `FUN_01018df8` — PASS (80 checks), `recon/ownership/net_private_7_recovery.json`
- `FUN_0101d890` — PASS (40 checks), `recon/analysis/net_private3_recovery_receipt.json`
- `FUN_0102665c` — PASS (44 checks), `recon/ownership/net_private_shard8_recovery.json`
- `FUN_010292ec` — PASS (40 checks), `recon/ownership/net_private_shard8_recovery.json`
- `FUN_0102a1e0` — PASS (40 checks), `recon/ownership/net_private_shard8_recovery.json`

## Post-baseline source changes

- `FUN_01009bc4`
- `FUN_01009c68`
- `FUN_010313ec`
- `FUN_01033888`
- `FUN_01033b18`
- `FUN_0103499c`

## Recheck tool hashes

- `tools/cfg_verify.py`: `bf7825359f1ba17dc401da3f27bfa17fc024e05dc42d0f866bbad11d1396aa04`
- `tools/net_extract.py`: `ec80c6ed622adce759db81b78a874dc70d9338215800e1d25c023ca08403a6d9`
- `tools/net_recon_kit.py`: `2ad1be0dfd9ffd53492fcfd8df8597e07942bb788c324457f2be169a4b7ec4ae`
- `tools/parity/emu.py`: `0e2503bbe2c517ee4c397a41ceec4e5e7e6d9e8ff26f5f5ff3257537f8e6ace0`
- `tools/parity/recon.py`: `22c5cc8d8113ac203fb96091fcffa392902dccd22792148958fcba40a4d5bbc2`
