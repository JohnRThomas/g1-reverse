# COLLISION-14 audit: `k_heap_free` at `0x00071b2c`

Status: **do not adopt the currently configured SDK object**. The identity and
ABI are correct, but the configured object is not firmware-equivalent because
spinlock validation and assertions were compiled out. Retain the reconstructed
body under a private namespace until the firmware-wide kernel configuration and
caller closure are complete.

## Firmware owner and true extent

The firmware function occupies exactly `0x00071b2c..0x00071bb8` (140 bytes,
SHA-256 `6867be49ffa3463ba0d43f79aad7501f62dfe7f8c5c115e8711741b1a52a8c71`).
The final instruction is the return at `0x00071bb6`. The six words beginning at
`0x00071bb8` are a separate literal pool, not executable code.

The ABI is the Zephyr public ABI:
`void k_heap_free(struct k_heap *heap, void *memory)`. Its state accesses also
agree with `struct k_heap`: the embedded spinlock is at `heap+0x14`, the
`sys_heap` begins at `heap+0x00`, and the wait queue is at `heap+0x0c`.

Unlike the configured object, the firmware executes both spin-validation
paths:

- save `BASEPRI`, raise it to `0x20`, and call `z_spin_lock_valid`;
- on failure, print the verbose assertion condition, source path, message, and
  invoke `assert_post_action`;
- call `z_spin_lock_set_owner`, `sys_heap_free`, and `z_unpend_all`;
- reschedule when waiters were released, otherwise call
  `z_spin_unlock_valid`, with a second verbose assertion path on failure;
- restore `BASEPRI` and return.

The literal pool resolves to the Zephyr spinlock source path, both validation
conditions, the verbose assertion format, and the “Invalid spinlock” / “Not my
spinlock” messages. Authoritative verification of the retained owner passes:
`FUN_00071b2c PASS cases=2`.

## Why the configured owner is not adoptable

The configured NCS 2.5.1 owner is
`zephyr/kernel/libkernel.a(kheap.c.obj)`, object SHA-256
`e9653b80186a9e44b9df52e123ec2d6afe85225cb661a75ee68fbbd36cf8ab86`.
Its source is `zephyr/kernel/kheap.c`, SHA-256
`8437e89784bcb0c8aa2dee29385b9b47d0bb9359fd2b20ce1bc96feebbffc86d`.

The configured `.text.k_heap_free` is only 58 bytes. It has three relocations:
`sys_heap_free`, `z_unpend_all`, and `z_reschedule`. It directly raises/restores
`BASEPRI`, but has no validation, owner-tracking, assertion calls, or assertion
data. The configured `.config` explicitly leaves `CONFIG_ASSERT` unset and
does not enable `CONFIG_SPIN_VALIDATE`. The collision audit correctly rejects
the signature (opcode `0.477612`, shape `0.388060`, length `0.340000`). This is
a side-effect and fault-policy mismatch, not relocatable-address noise.

## Source identity proved under the firmware configuration

Recompiling the same pinned `kheap.c` command with only:

```
CONFIG_ASSERT=1
CONFIG_ASSERT_LEVEL=2
CONFIG_SPIN_VALIDATE=1
```

produces a 164-byte section: 140 bytes of code followed by the same six literal
slots. After masking only the eleven call relocations at offsets
`28,42,50,58,64,72,80,94,100,114,122`, its 140 code bytes are exactly equal to
the firmware. Both normalized streams have SHA-256
`7a2371b481d24d8ec16a147741a2d7120969665df316b982eed461cdd7c20732`.

Therefore `k_heap_free` is the correct source identity, but the current build
configuration is not the firmware configuration. A one-symbol authorization
against the current 58-byte owner would be unsound.

## Complete recovered caller closure

The immediate adapter at `0x000868b4` converts an allocation payload pointer
to its four-byte heap header, loads the heap pointer, and tail-branches to
`k_heap_free`. It passes CFG verification with two cases.

Its direct callers are:

- `virtqueue_free` at `0x00070ee4` — CFG PASS, 2 cases;
- `svc_attr_memory_release` at `0x0007f3c2` — CFG PASS;
- `k_msgq_cleanup` at `0x00086480` — CFG PASS;
- `FUN_000864d0` — a 24-byte direct caller present in the firmware/reference
  graph but absent from the canonical reconstruction corpus.

The byte-exact veneer `thunk_FUN_000868b4` at `0x0007f978` also tail-branches
to the adapter; `FUN_0004f5b0` calls that veneer and passes CFG verification.
The missing `0x000864d0` body makes the reconstructed closure incomplete even
though every available node passes authoritative verification.

## Recommended implementation

1. Do not add a COLLISION-14 adoption authorization for the current build.
2. As the safe immediate integration step, namespace and retain the recovered
   firmware owner and its adapter so the configured 58-byte SDK owner cannot
   replace firmware behavior accidentally.
3. Recover and CFG-verify `0x000864d0`, then reconcile all adapter declarations
   to the real two-argument public `k_heap_free` boundary.
4. Treat `CONFIG_ASSERT=1`, `CONFIG_ASSERT_LEVEL=2`, and
   `CONFIG_SPIN_VALIDATE=1` as a firmware-wide configuration correction, not a
   per-function compiler flag. Rebuild and audit every affected kernel unit.
5. Only after that global rebuild and closure audit, adopt the exact SDK
   `k_heap_free` owner and remove the namespaced reconstruction. Until then,
   namespace retention is the fail-closed choice.

No naming, manifest, authorization, or retained-source mutation is made by
this audit.
