# CPUAPP reviewed interior/tail residues

This catalog is fail-closed: only exact four-byte Thumb tail branches and
exact same-entry historical spellings are materialized.

- Residue symbols: 119 (117 unique VAs)
- Materialized: 20 symbols (20 unique VAs)
- Already resolved by strong owners: 16 symbols
- Blocked: 83 symbols

| VA | Symbol | Decision | Target | Evidence/reason |
|---|---|---|---|---|
| `0x00016574` | `FUN_00016574` | `already_resolved_by_strong_owner` | `FUN_00016574` | ldr r3, [pc, #4]; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00016834` | `FUN_00016834` | `already_resolved_by_strong_owner` | `FUN_00016834` | cmp r0, #1; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x000179f8` | `FUN_000179f8` | `blocked` | `` | movs r1, #1; interior instruction or split entry has no exact alias/ABI proof |
| `0x00017a04` | `FUN_00017a04` | `already_resolved_by_strong_owner` | `FUN_00017a04` | movs r1, #0; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00017a10` | `FUN_00017a10` | `already_resolved_by_strong_owner` | `FUN_00017a10` | movs r1, #1; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00017a1c` | `FUN_00017a1c` | `already_resolved_by_strong_owner` | `FUN_00017a1c` | movs r1, #0; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00017a28` | `touch_pmic_reset_assert` | `already_resolved_by_strong_owner` | `touch_pmic_reset_assert` | movs r1, #1; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00017a34` | `touch_pmic_reset_deassert` | `already_resolved_by_strong_owner` | `touch_pmic_reset_deassert` | movs r1, #0; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00024e60` | `FUN_00024e60` | `blocked` | `` | movs r3, #0xfe; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0002538c` | `FUN_0002538c` | `blocked` | `` | push {r3, r4, r5, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000258b4` | `FUN_000258b4` | `blocked` | `` | push {r0, r1, r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00025950` | `FUN_00025950` | `blocked` | `` | push {r0, r1, r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0002893c` | `FUN_0002893c` | `already_resolved_by_strong_owner` | `FUN_0002893c` | push {r3, lr}; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00028964` | `FUN_00028964` | `blocked` | `` | push {r3, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0002bdf0` | `FUN_0002bdf0` | `blocked` | `` | push {r3, r4, r5, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00032fdc` | `FUN_00032fdc` | `already_resolved_by_strong_owner` | `FUN_00032fdc` | ldr r3, [pc, #4]; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00033554` | `FUN_00033554` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, sl, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0003364c` | `FUN_0003364c` | `blocked` | `` | push {r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00033730` | `FUN_00033730` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, sl, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00033a5c` | `FUN_00033a5c` | `blocked` | `` | push {r3, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00035744` | `FUN_00035744` | `blocked` | `` | push {r3, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0003603c` | `FUN_0003603c` | `blocked` | `` | movs r3, #0; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00036b3c` | `FUN_00036b3c` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0003cebc` | `ext3cebc` | `blocked` | `` | push {r0, r1, r2, r4, r5, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0003f410` | `FUN_0003f410` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0003fecc` | `FUN_0003fecc` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004372c` | `FUN_0004372c` | `blocked` | `` | push {r0, r1, r2, r3, r4, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004b3c8` | `FUN_0004b3c8` | `blocked` | `` | cmp.w r2, #0x40000; interior instruction or split entry has no exact alias/ABI proof |
| `0x0004c254` | `FUN_0004c254` | `blocked` | `` | cbz r0, #0x4c26a; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004d44c` | `FUN_0004d44c` | `blocked` | `` | push {r4, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004d468` | `FUN_0004d468` | `blocked` | `` | push {r4, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004d8b8` | `FUN_0004d8b8` | `blocked` | `` | push {r4, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004de68` | `FUN_0004de68` | `blocked` | `` | movw r3, #0x270f; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004e3e8` | `FUN_0004e3e8` | `blocked` | `` | movs r3, #0; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004e474` | `FUN_0004e474` | `blocked` | `` | movs r2, #0; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004e8c0` | `FUN_0004e8c0` | `blocked` | `` | push {r0, r1, r2, r3, r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0004f500` | `FUN_0004f500` | `blocked` | `` | cbz r0, #0x4f510; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00052fbc` | `FUN_00052fbc` | `blocked` | `` | push {r4, r5, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000534a8` | `FUN_000534a8` | `blocked` | `` | push {r0, r1, r2, r3, r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005463e` | `FUN_0005463e` | `blocked` | `` | svc #2; interior instruction or split entry has no exact alias/ABI proof |
| `0x00054688` | `FUN_00054688` | `blocked` | `` | svc #2; interior instruction or split entry has no exact alias/ABI proof |
| `0x00054d88` | `tail_54d88` | `blocked` | `` | push {r3, r4, r5, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00054ea8` | `FUN_00054ea8` | `blocked` | `` | movs r1, #0; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00055aac` | `FUN_00055aac` | `blocked` | `` | push {r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000564cc` | `FUN_000564cc` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000573c8` | `FUN_000573c8` | `blocked` | `` | push {r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00058568` | `FUN_00058568` | `blocked` | `` | push {r0, r1, r2, r3, r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005a954` | `FUN_0005a954` | `blocked` | `` | movs r1, #1; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005ad38` | `FUN_0005ad38` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005c310` | `FUN_0005c310` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005c6c8` | `ext5c6c8` | `blocked` | `` | push {r4, r5, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005c76c` | `FUN_0005c76c` | `blocked` | `` | push {r3, r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005c9a4` | `FUN_0005c9a4` | `blocked` | `` | push.w {r0, r1, r2, r4, r5, r6, r7, r8, sb, sl, fp, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0005ce6c` | `FUN_0005ce6c` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00061200` | `tail_61200` | `blocked` | `` | push {r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0006446c` | `FUN_0006446c` | `blocked` | `` | cmp r4, #0; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0006447c` | `FUN_0006447c` | `blocked` | `` | push {r3, r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00065000` | `FUN_00065000` | `blocked` | `` | mov.w r3, #0x50005000; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00066524` | `FUN_00066524` | `blocked` | `` | push {r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000680f8` | `FUN_000680f8` | `blocked` | `` | push {r4, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00068298` | `FUN_00068298` | `blocked` | `` | push {r3, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00071560` | `FUN_00071560` | `blocked` | `` | push {r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000715b8` | `FUN_000715b8` | `blocked` | `` | push {r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00071b2c` | `FUN_00071b2c` | `blocked` | `` | push {r3, r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000723b8` | `thunk_FUN_000723b8` | `materialize_reviewed_same_entry_alias` | `k_mutex_lock` | push.w {r0, r1, r4, r5, r6, r7, r8, lr}; historical spelling shares the exact catalog entry |
| `0x00072558` | `thunk_FUN_00072558` | `materialize_reviewed_same_entry_alias` | `k_mutex_unlock` | push {r4, r5, r6, lr}; historical spelling shares the exact catalog entry |
| `0x00072908` | `k_sem_take` | `blocked` | `` | push {r0, r1, r2, r4, r5, r6, r7, lr}; SDK/config public owner is outside this interior-alias pass |
| `0x0007332c` | `FUN_0007332c` | `blocked` | `` | push {r0, r1, r2, r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00073424` | `FUN_00073424` | `blocked` | `` | push {r0, r1, r2, r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00074184` | `FUN_00074184` | `blocked` | `` | push {r3, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000748b8` | `FUN_000748b8` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00075864` | `FUN_00075864` | `blocked` | `` | adds r2, #4; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000758cc` | `FUN_000758cc` | `blocked` | `` | cmp r0, #3; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00075e14` | `FUN_00075e14` | `blocked` | `` | ldr r2, [pc, #0x16c]; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00076a88` | `FUN_00076a88` | `blocked` | `` | vldr s0, [pc, #4]; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00076bc0` | `FUN_00076bc0` | `blocked` | `` | ldr r0, [pc, #4]; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00077b24` | `FUN_00077b24` | `blocked` | `` | mov r3, r2; interior instruction or split entry has no exact alias/ABI proof |
| `0x00077b38` | `FUN_00077b38` | `blocked` | `` | push.w {r4, r5, r6, r7, r8, sb, lr}; interior instruction or split entry has no exact alias/ABI proof |
| `0x00077c4c` | `FUN_00077c4c` | `blocked` | `` | push {lr}; interior instruction or split entry has no exact alias/ABI proof |
| `0x00077c8c` | `ext77c8c` | `blocked` | `` | push {r3, r4, r5, r6, r7, lr}; interior instruction or split entry has no exact alias/ABI proof |
| `0x00077d30` | `tail_77d30` | `blocked` | `` | push {r3, r4, r5, lr}; interior instruction or split entry has no exact alias/ABI proof |
| `0x0007c010` | `FUN_0007c010` | `materialize_reviewed_tail_alias` | `k_sem_give` | b.w #0x72880; exact four-byte unconditional Thumb tail branch |
| `0x0007c058` | `send_touch_click_event` | `blocked` | `` | movs r1, #0; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0007c084` | `FUN_0007c084` | `blocked` | `` | mov r2, r1; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0007c0a4` | `FUN_0007c0a4` | `materialize_reviewed_tail_alias` | `FUN_00074844` | b.w #0x74844; exact four-byte unconditional Thumb tail branch |
| `0x0007c872` | `FUN_0007c872` | `materialize_reviewed_tail_alias` | `k_mutex_lock` | b.w #0x723b8; exact four-byte unconditional Thumb tail branch |
| `0x0007c876` | `FUN_0007c876` | `materialize_reviewed_tail_alias` | `k_mutex_unlock` | b.w #0x72558; exact four-byte unconditional Thumb tail branch |
| `0x0007ca72` | `FUN_0007ca72` | `materialize_reviewed_tail_alias` | `FUN_00074844` | b.w #0x74844; exact four-byte unconditional Thumb tail branch |
| `0x0007cb48` | `thunk_FUN_00072908` | `already_resolved_by_strong_owner` | `z_impl_k_sem_take` | b.w #0x72908; exact four-byte unconditional Thumb tail branch |
| `0x0007cb48` | `update_sync_buffer` | `already_resolved_by_strong_owner` | `z_impl_k_sem_take` | b.w #0x72908; exact four-byte unconditional Thumb tail branch |
| `0x0007cb4c` | `process_sync_buffer` | `already_resolved_by_strong_owner` | `k_sem_give` | b.w #0x72880; exact four-byte unconditional Thumb tail branch |
| `0x0007cb50` | `process_touch_event` | `materialize_reviewed_tail_alias` | `mutex_unlock_syscall_handler` | b.w #0x745c8; exact four-byte unconditional Thumb tail branch |
| `0x0007cb8a` | `thunk_FUN_00074844` | `already_resolved_by_strong_owner` | `FUN_00074844` | b.w #0x74844; exact four-byte unconditional Thumb tail branch |
| `0x0007cb8a` | `wait_for_event` | `materialize_reviewed_tail_alias` | `FUN_00074844` | b.w #0x74844; exact four-byte unconditional Thumb tail branch |
| `0x0007ce5c` | `FUN_0007ce5c` | `materialize_reviewed_tail_alias` | `FUN_00074844` | b.w #0x74844; exact four-byte unconditional Thumb tail branch |
| `0x0007d376` | `FUN_0007d376` | `materialize_reviewed_tail_alias` | `k_mutex_lock` | b.w #0x723b8; exact four-byte unconditional Thumb tail branch |
| `0x0007d37a` | `FUN_0007d37a` | `materialize_reviewed_tail_alias` | `k_mutex_unlock` | b.w #0x72558; exact four-byte unconditional Thumb tail branch |
| `0x0007d3be` | `thunk_FUN_00043308` | `materialize_reviewed_tail_alias` | `gui_reset_dynamic_bitmap_frame_state` | b.w #0x43308; exact four-byte unconditional Thumb tail branch |
| `0x0007d63e` | `thunk_FUN_0007d77c` | `materialize_reviewed_tail_alias` | `projector_send_cmd_immediate` | b.w #0x7d77c; exact four-byte unconditional Thumb tail branch |
| `0x0007e12a` | `FUN_0007e12a` | `blocked` | `` | push {r4, r5, r6, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x0007ef56` | `FUN_0007ef56` | `blocked` | `` | ldr r3, [r0, #0x14]; interior instruction or split entry has no exact alias/ABI proof |
| `0x0007f7c4` | `thunk_FUN_0007f7d2` | `blocked` | `` | b.w #0x7f7d2; exact tail target has no retained or adopted owner |
| `0x0007f978` | `thunk_FUN_000868b4` | `materialize_reviewed_tail_alias` | `FUN_000868b4` | b.w #0x868b4; exact four-byte unconditional Thumb tail branch |
| `0x00080294` | `FUN_00080294_i` | `materialize_reviewed_same_entry_alias` | `tc_cmac_final` | push {r4, r5, r6, lr}; historical spelling shares the exact catalog entry |
| `0x0008131c` | `FUN_0008131c` | `blocked` | `` | b.w #0x812d2; exact tail target has no retained or adopted owner |
| `0x000836e8` | `thunk_FUN_000727ac` | `already_resolved_by_strong_owner` | `FUN_000727ac` | b.w #0x727ac; exact four-byte unconditional Thumb tail branch |
| `0x00083a2c` | `FUN_00083a2c` | `blocked` | `` | push.w {r0, r1, r4, r5, r6, r7, r8, lr}; interior instruction or split entry has no exact alias/ABI proof |
| `0x00084e44` | `FUN_00084e44` | `blocked` | `` | push {r0, r1, r2, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00084f06` | `FUN_00084f06` | `blocked` | `` | cbz r0, #0x84f0e; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000859b2` | `FUN_000859b2` | `materialize_reviewed_tail_alias` | `k_sem_give` | b.w #0x72880; exact four-byte unconditional Thumb tail branch |
| `0x00085c86` | `FUN_00085c86` | `blocked` | `` | push {r3, r4, r5, r6, r7, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00085cf2` | `thunk_FUN_00085cf2` | `materialize_reviewed_same_entry_alias` | `FUN_00085cf2` | push {r4, lr}; historical spelling shares the exact catalog entry |
| `0x00085ef0` | `FUN_00085ef0` | `blocked` | `` | push {r3, r4, r5, lr}; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x000861aa` | `FUN_000861aa` | `materialize_reviewed_tail_alias` | `FUN_00085cf2` | b.w #0x85cf2; exact four-byte unconditional Thumb tail branch |
| `0x00086228` | `FUN_00086228` | `already_resolved_by_strong_owner` | `zcbor_str_encode` | push.w {r4, r5, r6, r7, r8, sb, sl, lr}; exact standalone entry reconstructed and CFG-side-effect verified |
| `0x00086360` | `FUN_00086360` | `blocked` | `` | push {r0, r1, r2, lr}; interior instruction or split entry has no exact alias/ABI proof |
| `0x0008641c` | `FUN_0008641c` | `materialize_reviewed_tail_alias` | `sched_thread_ready` | b.w #0x73a78; exact four-byte unconditional Thumb tail branch |
| `0x0008664c` | `FUN_0008664c` | `blocked` | `` | mov.w r3, #0x20; uncatalogued candidate entry; proximity or a prologue is not ABI evidence |
| `0x00086698` | `uptime_ticks_get` | `already_resolved_by_strong_owner` | `k_uptime_ticks_impl` | b.w #0x74f68; exact four-byte unconditional Thumb tail branch |
