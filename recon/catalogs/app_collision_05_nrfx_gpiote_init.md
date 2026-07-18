# COLLISION-05 — `nrfx_gpiote_init`

Decision: **retain the reconstruction; SDK adoption denied**.

The retained firmware body is isolated as `g1_recon_nrfx_gpiote_init`, with the raw `FUN_00065940 @ 0x00065940` back-map preserved. The configured SDK keeps the public `nrfx_gpiote_init` spelling; no adoption overlay or exclusion is used.

The configured SDK body is not firmware-exact. Its normalized opcode score is `0.608696` and operand-shape score is `0.579710`; the firmware body is 104 bytes while the SDK body is 80 bytes.

The firmware initialization path clears and reads back eight indexed IN events before clearing PORT. The configured SDK object clears PORT only. A forced uninitialized-state differential probe fails at call ordinal 1: firmware calls `0x000655ec`; SDK behavior proceeds to `arch_irq_enable` at `0x000500ac`.

There is also a state-ownership mismatch: firmware `g_gpiote_cb` is pinned at `0x20002bc0`, while the configured SDK object's local `m_cb` links at `0x2000050c`.

## Required closure before adoption

1. reconcile the pinned NRFX/HAL configuration until the SDK owner performs the firmware eight-event clear/readback sequence
2. pin or otherwise reconcile nrfx_gpiote.c's local .data.m_cb with firmware g_gpiote_cb at 0x20002bc0
3. enumerate and verify every nrfx_gpiote.c public/private function and every raw external access to the shared control block
4. authoritatively verify state-zero and already-initialized paths before any whole-unit adoption
5. only then authorize exclusion and require an isolated retain-all collision delta of exactly -1 with sole SDK map/nm ownership
