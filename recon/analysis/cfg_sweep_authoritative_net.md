# Authoritative CPUNET CFG sweep

This checkpoint binds all generic-sweep verdicts to the exact frozen 1,090-source canonical CPUNET inventory and verifier tool hashes.

- Source inventory digest: `996c31f47c654baf1f373e351f9a4168eb7cfbab24974ce93837cf51366517f5`
- Result: **1073 PASS, 8 FAIL, 0 compile error, 8 OTHER, 1 timeout, 0 source drift**
- Unresolved by this generic sweep: **17**

## Post-sweep repair drift

Six failing sources were repaired after their frozen lane verdicts and before this baseline was committed. Their baseline FAIL verdicts and pre-repair source hashes remain unchanged here; repair rechecks must be captured as separate overlay receipts.

- `FUN_01009bc4`
- `FUN_01009c68`
- `FUN_010313ec`
- `FUN_01033888`
- `FUN_01033b18`
- `FUN_0103499c`

## FAIL

- `FUN_01008d00`
- `FUN_01009bc4`
- `FUN_01009c68`
- `FUN_0101ab20`
- `FUN_010313ec`
- `FUN_01033888`
- `FUN_01033b18`
- `FUN_0103499c`

## Timeout

- `FUN_010089f8`

## Catalog-missed OTHER

The generic CFG sweep inventories every canonical source, but cannot derive original size/CFG for sources absent from the net_funcs catalog. Those eight entries are fail-closed as OTHER; their dedicated reconstruction receipts are mapped here and are not promoted to generic-sweep PASS.

- `FUN_0100ef08` (`0x0100ef08`) — dedicated receipt: `recon/ownership/net_private_shard8_recovery.json`
- `FUN_01011664` (`0x01011664`) — dedicated receipt: `recon/ownership/net_private_7_recovery.json`
- `FUN_01014b18` (`0x01014b18`) — dedicated receipt: `recon/ownership/net_private_shard1.json`
- `FUN_01018df8` (`0x01018df8`) — dedicated receipt: `recon/ownership/net_private_7_recovery.json`
- `FUN_0101d890` (`0x0101d890`) — dedicated receipt: `recon/analysis/net_private3_recovery_receipt.json`
- `FUN_0102665c` (`0x0102665c`) — dedicated receipt: `recon/ownership/net_private_shard8_recovery.json`
- `FUN_010292ec` (`0x010292ec`) — dedicated receipt: `recon/ownership/net_private_shard8_recovery.json`
- `FUN_0102a1e0` (`0x0102a1e0`) — dedicated receipt: `recon/ownership/net_private_shard8_recovery.json`

## Tool hashes

- `tools/cfg_verify.py`: `6c178d90d1b1ba7c3896b353c73776ce7aa09a524a05edbe26f05a03d72c9152`
- `tools/parity/emu.py`: `0e2503bbe2c517ee4c397a41ceec4e5e7e6d9e8ff26f5f5ff3257537f8e6ace0`
- `tools/parity/recon.py`: `22c5cc8d8113ac203fb96091fcffa392902dccd22792148958fcba40a4d5bbc2`
- `tools/reverify.py`: `97aeacd67d84e76958c987ad710ba75def44a479fa8c9172a159338f8f9321c9`
