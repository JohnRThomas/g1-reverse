# COLLISION-21 fail-closed report: recursive newlib retarget locks

Decision: **retain and namespace both firmware reconstructions; do not adopt the configured Zephyr object**.

The `_LOCK_T` ABI and valid mutex operations agree, and neither hook owns global state. The decisive difference is the active firmware `lock != NULL` assertion path. The configured object compiled that path out and contains only a mutex tail-call.

| Hook | Firmware / SDK bytes | Opcode / shape | CFG retained / SDK semantics | Direct sites |
|---|---:|---:|---:|---:|
| `__retarget_lock_acquire_recursive` | 44 / 12 | 0.352941 / 0.352941 | PASS 2 / FAIL 1 | 6 |
| `__retarget_lock_release_recursive` | 36 / 4 | 0.153846 / 0.153846 | PASS 2 / FAIL 1 | 7 |

Both true extents end at their tail branches; the assertion literal pools begin immediately afterward and are not part of either code extent.

## Implementation closure

1. namespace both retained hooks and preserve FUN_000510fc/FUN_00051134 address back-maps
2. regenerate all six acquire and seven release direct call sites; FUN_00076ed4 owns two release sites
3. keep the configured libc-hooks.c public hooks intact and create no adoption overlay or exclusion
4. require retain-all collision delta -2 with no new unresolved symbols and distinct SDK/namespaced map owners
5. future SDK adoption is permitted only after rebuilding libc-hooks.c with the firmware assertion policy and proving the complete source unit
