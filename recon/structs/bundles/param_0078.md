### cluster param_0078  (param, 1 members, 2 fields, size>=0x1058)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - update_persist_task_status_to_wait_blow_head @ 0x2c180  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0078 {
    uint8_t    _pad_0x0[0xd5];   /* +0x0 pad */
    uint8_t    field_0xd5;   /* +0xd5  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xd6[0xf7e];   /* +0xd6 pad */
    void *     field_0x1054;   /* +0x1054  sz=4 rw=r types=int,ptr */
};
```