# CPUAPP interior/tail alias audit

The current 9-entry residue snapshot was reviewed against the shipped
Thumb bytes, catalog boundaries, and canonical call sites. No linker
aliases, weak owners, blobs, or derivative trees are generated.

- Same-entry aliases/identities: 1
- Legitimate interior tails/islands: 3
- SDK static/library identities: 3
- Data/literal misreferences: 0
- True missing catalog entries: 2
- Safe canonical caller corrections: 3

| VA | Symbol | Classification | Resolution | Evidence |
|---|---|---|---|---|
| `0x0004d7d8` | `FUN_0004d7d8` | `sdk_static_or_library_identity` | `already_resolved_by_cfg_verified_strong_owner` | push {r0, r1, r4, lr}; ldr r0, [pc, #0xac]; exact-entry strong owner accepted by cfg_verify |
| `0x0005463e` | `FUN_0005463e` | `legitimate_interior_tail_or_island` | `blocked_embedded_noreturn_svc_island` | svc #2; mov.w sl, #3; embedded SVC continuation is not an ordinary function ABI |
| `0x00054688` | `FUN_00054688` | `legitimate_interior_tail_or_island` | `blocked_embedded_noreturn_svc_island` | svc #2; ldr.w fp, [pc, #0xf4]; embedded SVC continuation is not an ordinary function ABI |
| `0x00056e24` | `FUN_00056e24` | `sdk_static_or_library_identity` | `already_resolved_by_cfg_verified_strong_owner` | ldr r3, [pc, #8]; ldr r2, [r3]; exact-entry strong owner accepted by cfg_verify |
| `0x00077a28` | `strtol_reentrant` | `sdk_static_or_library_identity` | `already_resolved_by_cfg_verified_strong_owner` | cmp r3, #0x24; push.w {r4, r5, r6, r7, r8, sb, sl, lr}; exact-entry strong owner accepted by cfg_verify |
| `0x00077c8c` | `ext77c8c` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push {r3, r4, r5, r6, r7, lr}; mov r6, r1; exact-entry strong owner accepted by cfg_verify |
| `0x00077d30` | `tail_77d30` | `true_missing_catalog_entry` | `already_resolved_by_cfg_verified_strong_owner` | push {r3, r4, r5, lr}; mov r4, r0; exact-entry strong owner accepted by cfg_verify |
| `0x0007f7c4` | `thunk_FUN_0007f7d2` | `same_entry_alias` | `already_resolved_by_cfg_verified_strong_owner` | b.w #0x7f7d2; ldr.w r3, [r0, #0x864]; exact-entry strong owner accepted by cfg_verify |
| `0x0008131c` | `FUN_0008131c` | `legitimate_interior_tail_or_island` | `already_resolved_by_cfg_verified_strong_owner` | b.w #0x812d2; adds r0, #0x18; exact-entry strong owner accepted by cfg_verify |
