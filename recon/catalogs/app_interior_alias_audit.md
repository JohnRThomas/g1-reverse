# CPUAPP interior/tail alias audit

The current 66-entry residue snapshot was reviewed against the shipped
Thumb bytes, catalog boundaries, and canonical call sites. No linker
aliases, weak owners, blobs, or derivative trees are generated.

- Same-entry aliases/identities: 1
- Legitimate interior tails/islands: 4
- Data/literal misreferences: 0
- True missing catalog entries: 61
- Safe canonical caller corrections: 1

| VA | Symbol | Classification | Resolution | Evidence |
|---|---|---|---|---|
| `0x000179f8` | `FUN_000179f8` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | movs r1, #1; ldr r0, [pc, #4]; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x00026100` | `FUN_00026100` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push.w {r3, r4, r5, r6, r7, r8, sb, sl, fp, lr}; mov r4, r0; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x00033554` | `FUN_00033554` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push.w {r4, r5, r6, r7, r8, sb, sl, lr}; mov r8, r2; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x00033730` | `FUN_00033730` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push.w {r4, r5, r6, r7, r8, sb, sl, lr}; movs r4, #0; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x0003603c` | `FUN_0003603c` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | movs r3, #0; push.w {r0, r1, r2, r4, r5, r6, r7, r8, sb, lr}; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x00036b3c` | `FUN_00036b3c` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; sub sp, #0x24; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x0003f410` | `FUN_0003f410` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; sub sp, #0x34; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x0003fecc` | `FUN_0003fecc` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; mov sb, r0; standalone exact-entry reconstruction accepted by cfg_verify |
| `0x0004b3c8` | `FUN_0004b3c8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | cmp.w r2, #0x40000; push.w {r4, r5, r6, r7, r8, lr}; independent callable entry shape/reference, absent from catalog |
| `0x0004c254` | `FUN_0004c254` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | cbz r0, #0x4c26a; ldr r3, [pc, #0x14]; independent callable entry shape/reference, absent from catalog |
| `0x0004d44c` | `FUN_0004d44c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, lr}; ldr r4, [pc, #0x10]; independent callable entry shape/reference, absent from catalog |
| `0x0004d468` | `FUN_0004d468` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, lr}; mov r4, r0; independent callable entry shape/reference, absent from catalog |
| `0x0004d8b8` | `FUN_0004d8b8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, lr}; ldr r3, [pc, #0x18]; independent callable entry shape/reference, absent from catalog |
| `0x0004de68` | `FUN_0004de68` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | movw r3, #0x270f; push {r0, r1, r4, r5, r6, lr}; independent callable entry shape/reference, absent from catalog |
| `0x0004e3e8` | `FUN_0004e3e8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | movs r3, #0; push {r4, r5, lr}; independent callable entry shape/reference, absent from catalog |
| `0x0004e474` | `FUN_0004e474` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | movs r2, #0; ldr r3, [pc, #8]; independent callable entry shape/reference, absent from catalog |
| `0x0004e8c0` | `FUN_0004e8c0` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r0, r1, r2, r3, r4, r5, r6, lr}; ldr r3, [pc, #0x1c]; independent callable entry shape/reference, absent from catalog |
| `0x0004f500` | `FUN_0004f500` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | cbz r0, #0x4f510; ldr r3, [pc, #0x10]; independent callable entry shape/reference, absent from catalog |
| `0x000534a8` | `FUN_000534a8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r0, r1, r2, r3, r4, r5, r6, lr}; ldr r3, [pc, #0x18]; independent callable entry shape/reference, absent from catalog |
| `0x0005463e` | `FUN_0005463e` | `legitimate_interior_tail_or_island` | `blocked_embedded_noreturn_svc_island` | svc #2; mov.w sl, #3; embedded SVC continuation is not an ordinary function ABI |
| `0x00054688` | `FUN_00054688` | `legitimate_interior_tail_or_island` | `blocked_embedded_noreturn_svc_island` | svc #2; ldr.w fp, [pc, #0xf4]; embedded SVC continuation is not an ordinary function ABI |
| `0x00054d88` | `tail_54d88` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, lr}; movs r2, #6; independent callable entry shape/reference, absent from catalog |
| `0x00054ea8` | `FUN_00054ea8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | movs r1, #0; push {r4, r5, r6, r7, lr}; independent callable entry shape/reference, absent from catalog |
| `0x00055aac` | `FUN_00055aac` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, r5, r6, r7, lr}; sub sp, #0xc; independent callable entry shape/reference, absent from catalog |
| `0x000564cc` | `FUN_000564cc` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r4, r5, r6, r7, r8, sb, lr}; sub sp, #0x1c; independent callable entry shape/reference, absent from catalog |
| `0x000573c8` | `FUN_000573c8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r7, lr}; add r7, sp, #0; independent callable entry shape/reference, absent from catalog |
| `0x00058568` | `FUN_00058568` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r0, r1, r2, r3, r4, r5, r6, lr}; ldr r3, [pc, #0x18]; independent callable entry shape/reference, absent from catalog |
| `0x0005a954` | `FUN_0005a954` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | movs r1, #1; push {r4, lr}; independent callable entry shape/reference, absent from catalog |
| `0x0005ad38` | `FUN_0005ad38` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; sub sp, #0x24; independent callable entry shape/reference, absent from catalog |
| `0x0005c310` | `FUN_0005c310` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r4, r5, r6, r7, r8, sb, lr}; ldrh r6, [r3, #0xc]; independent callable entry shape/reference, absent from catalog |
| `0x0005c6c8` | `ext5c6c8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, r5, r7, lr}; sub sp, #0x38; independent callable entry shape/reference, absent from catalog |
| `0x0005c76c` | `FUN_0005c76c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, r6, r7, lr}; mov r5, r0; independent callable entry shape/reference, absent from catalog |
| `0x0005c9a4` | `FUN_0005c9a4` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r0, r1, r2, r4, r5, r6, r7, r8, sb, sl, fp, lr}; mov r4, r0; independent callable entry shape/reference, absent from catalog |
| `0x0005ce6c` | `FUN_0005ce6c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r4, r5, r6, r7, r8, lr}; sub sp, #0x18; independent callable entry shape/reference, absent from catalog |
| `0x00061200` | `tail_61200` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r7, lr}; add r7, sp, #0; independent callable entry shape/reference, absent from catalog |
| `0x0006446c` | `FUN_0006446c` | `legitimate_interior_tail_or_island` | `caller_corrected_to_internal_failure_result` | cmp r4, #0; bne.w #0x6433e; depends on parent live r4 and branches back into parent CFG |
| `0x0006447c` | `FUN_0006447c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, r6, r7, lr}; mov r5, r1; independent callable entry shape/reference, absent from catalog |
| `0x00065000` | `FUN_00065000` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | mov.w r3, #0x50005000; movs r2, #0; independent callable entry shape/reference, absent from catalog |
| `0x000680f8` | `FUN_000680f8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, lr}; ldrd r1, r2, [r0, #0x24]; independent callable entry shape/reference, absent from catalog |
| `0x00068298` | `FUN_00068298` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, lr}; ldr r0, [pc, #8]; independent callable entry shape/reference, absent from catalog |
| `0x00071560` | `FUN_00071560` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, r5, r6, r7, lr}; mov r5, r0; independent callable entry shape/reference, absent from catalog |
| `0x000715b8` | `FUN_000715b8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, r5, r6, lr}; mov r4, r3; independent callable entry shape/reference, absent from catalog |
| `0x00071b2c` | `FUN_00071b2c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, r6, r7, lr}; mov r5, r0; independent callable entry shape/reference, absent from catalog |
| `0x00074184` | `FUN_00074184` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, lr}; bl #0x74060; independent callable entry shape/reference, absent from catalog |
| `0x000748b8` | `FUN_000748b8` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r4, r5, r6, r7, r8, lr}; mov r4, r0; independent callable entry shape/reference, absent from catalog |
| `0x00075864` | `FUN_00075864` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | adds r2, #4; push.w {r0, r1, r4, r5, r6, r8, sb, lr}; independent callable entry shape/reference, absent from catalog |
| `0x000758cc` | `FUN_000758cc` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | cmp r0, #3; mov r2, r1; independent callable entry shape/reference, absent from catalog |
| `0x00075e14` | `FUN_00075e14` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | ldr r2, [pc, #0x16c]; push.w {r4, r5, r6, r7, r8, lr}; independent callable entry shape/reference, absent from catalog |
| `0x00076bc0` | `FUN_00076bc0` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | ldr r0, [pc, #4]; b.w #0x51134; independent callable entry shape/reference, absent from catalog |
| `0x00077b24` | `FUN_00077b24` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | mov r3, r2; mov r2, r1; independent callable entry shape/reference, absent from catalog |
| `0x00077b38` | `FUN_00077b38` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r4, r5, r6, r7, r8, sb, lr}; mov lr, r0; independent callable entry shape/reference, absent from catalog |
| `0x00077c4c` | `FUN_00077c4c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {lr}; sub sp, #0x6c; independent callable entry shape/reference, absent from catalog |
| `0x00077c8c` | `ext77c8c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, r6, r7, lr}; mov r6, r1; independent callable entry shape/reference, absent from catalog |
| `0x00077d30` | `tail_77d30` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, lr}; mov r4, r0; independent callable entry shape/reference, absent from catalog |
| `0x0007e12a` | `FUN_0007e12a` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r4, r5, r6, lr}; ldr r6, [r0]; independent callable entry shape/reference, absent from catalog |
| `0x0007ef56` | `FUN_0007ef56` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | ldr r3, [r0, #0x14]; cbz r3, #0x7ef6c; independent callable entry shape/reference, absent from catalog |
| `0x0007f7c4` | `thunk_FUN_0007f7d2` | `same_entry_alias` | `blocked_same_entry_identity_without_target_owner` | b.w #0x7f7d2; ldr.w r3, [r0, #0x864]; catalog entry 0x0007f7c4 branches to ownerless 0x0007f7d2 |
| `0x0008131c` | `FUN_0008131c` | `legitimate_interior_tail_or_island` | `blocked_tail_target_has_no_strong_owner` | b.w #0x812d2; adds r0, #0x18; exact branch to 0x000812d2, but target is not retained |
| `0x00083a2c` | `FUN_00083a2c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push.w {r0, r1, r4, r5, r6, r7, r8, lr}; mov r4, r3; independent callable entry shape/reference, absent from catalog |
| `0x00084e44` | `FUN_00084e44` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r0, r1, r2, lr}; movs r3, #1; independent callable entry shape/reference, absent from catalog |
| `0x00084f06` | `FUN_00084f06` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | cbz r0, #0x84f0e; ldr r0, [r0, #8]; independent callable entry shape/reference, absent from catalog |
| `0x00085c86` | `FUN_00085c86` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, r6, r7, lr}; ldr r6, [r0, #0x14]; independent callable entry shape/reference, absent from catalog |
| `0x00085ef0` | `FUN_00085ef0` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r3, r4, r5, lr}; mov r4, r0; independent callable entry shape/reference, absent from catalog |
| `0x00086228` | `FUN_00086228` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push.w {r4, r5, r6, r7, r8, sb, sl, lr}; ldr r6, [r0]; standalone zcbor string encoder recovered at its exact entry |
| `0x00086360` | `FUN_00086360` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | push {r0, r1, r2, lr}; movs r3, #1; independent callable entry shape/reference, absent from catalog |
| `0x0008664c` | `FUN_0008664c` | `true_missing_catalog_entry` | `requires_independent_reconstruction` | mov.w r3, #0x20; mrs r0, basepri; independent callable entry shape/reference, absent from catalog |
