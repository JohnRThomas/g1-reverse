# COLLISION-17: `z_impl_k_queue_init` ownership audit

Decision: **retain the firmware initializer under a namespaced symbol; do not adopt the configured `queue.c` owner.** This audit is report-only and authorizes no naming, manifest, or retained-source mutation.

The one-pointer ABI and high mnemonic similarity are misleading. Firmware `0x864e8` is 26 bytes (eight instructions) and initializes a 28-byte queue layout. It clears `data_q` at `+0..+7`, explicitly clears a four-byte spinlock at `+8`, initializes `wait_q` at `+0xc`, and initializes `poll_events` at `+0x14`.

The selected NCS 2.5.1 `zephyr/kernel/queue.c` owner is 24 bytes (seven instructions). Its configured `k_spinlock` is zero-sized (`CONFIG_SMP=n`, `CONFIG_SPIN_VALIDATE=n`), so it initializes `wait_q` at `+8` and `poll_events` at `+0x10`. There are no relocations that could explain or mask the difference. Substitution would write both lists four bytes too early and would not clear the firmware lock word.

The firmware extent is exact: `[0x864e8, 0x86502)`, immediately followed by the distinct function at `0x86502`. Authoritative CFG verification passes for the owner and all ten callers. The complete all-image closure is 11 direct call sites across ten callers; `bt_att_accept` contains two sites. Addresses, caller identities, hashes, state-write layouts, and CFG results are pinned in the JSON audit.

Recommended later implementation: assign `0x864e8` a non-colliding firmware name, preserve `k_fifo_init` as a raw back-map/alias where needed, and retarget all 11 recorded firmware sites. Keep the configured SDK owner available for correctly configured SDK consumers, but never exclude this firmware body in its favor.
